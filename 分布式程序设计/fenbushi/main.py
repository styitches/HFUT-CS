# coding:utf-8
import urllib.request
import urllib.error
import json
import csv
import os


class WeatherCrawler:
    def __init__(self):
        pass

    def get_html(self, url):
        try:
            response = urllib.request.urlopen(url)
            return response.read().decode("utf-8")
        except urllib.error.URLError as e:
            print(f"Error fetching data from {url}: {e}")
            return None

    def parse_json(self, url):
        json_data = self.get_html(url)
        return json.loads(json_data) if json_data else []

    def write_to_csv(self, file, data, is_header=False):
        mode = 'w' if is_header else 'a+'
        with open(file, mode, newline="", encoding='utf-8-sig') as csv_file:
            csv_writer = csv.writer(csv_file)
            if is_header:
                csv_writer.writerow(data[0].keys())
            csv_writer.writerows(map(lambda x: x.values(), data))

    def read_csv(self, file):
        try:
            with open(file, 'r', encoding='utf-8-sig') as f:
                data = csv.DictReader(f)
                return list(data)
        except FileNotFoundError:
            return []

    def crawl_and_write_data(self, file, url, header_data=None):
        if not os.path.exists(file):
            print(f"Begin crawling data from {url}")
            data = self.parse_json(url)
            if header_data:
                data.insert(0, header_data)
            self.write_to_csv(file, data, is_header=True)
            print(f"End crawling data from {url}")
        else:
            print(f"Data already exists in {file}")

    def get_provinces(self):
        province_file = 'province.csv'
        provinces = self.read_csv(province_file)
        if not provinces:
            print("Crawling province data...")
            provinces = self.parse_json('http://www.nmc.cn/f/rest/province')
            self.write_to_csv(province_file, provinces, is_header=True)
        return provinces

    def get_cities(self):
        city_file = 'city.csv'
        cities = self.read_csv(city_file)
        if not cities:
            print("Crawling city data...")
            provinces = self.get_provinces()
            for province in provinces:
                url = province['url'].split('/')[-1].split('.')[0]
                cities.extend(self.parse_json(f'http://www.nmc.cn/f/rest/province/{url}'))
            self.write_to_csv(city_file, cities, is_header=True)
        return cities

    def get_passed_weather(self):
        weather_passed_file = 'weather.csv'
        if os.path.exists(weather_passed_file):
            print("Passed weather data already exists.")
            return

        passed_weather = []
        count = 0

        print("Begin crawling passed weather data...")

        for city in self.get_cities():
            print(f"{city['province']} {city['city']} {city['code']}")
            data = self.parse_json(f'http://www.nmc.cn/f/rest/passed/{city["code"]}')

            if data:
                count += 1
                for item in data:
                    item['province'] = city['province']
                    item['city_name'] = city['city']
                passed_weather.extend(data)

            if count % 50 == 0:
                if count == 50:
                    self.write_to_csv(weather_passed_file, passed_weather, is_header=True)
                else:
                    self.write_to_csv(weather_passed_file, passed_weather)
                passed_weather = []

        if passed_weather:
            if count <= 50:
                self.write_to_csv(weather_passed_file, passed_weather, is_header=True)
            else:
                self.write_to_csv(weather_passed_file, passed_weather)

        print("End crawling passed weather data.")


if __name__ == '__main__':
    crawler = WeatherCrawler()
    crawler.get_passed_weather()
