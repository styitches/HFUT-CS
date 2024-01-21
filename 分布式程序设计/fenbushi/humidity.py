from pyspark.sql import SparkSession
from pyspark.sql import functions as F
from pyspark.sql.types import DecimalType

def passed_humidity_analyse(filename):
    print("begin to analyse passed humidity")
    spark = SparkSession.builder.master("local").appName("passed_humidity_analyse").getOrCreate()
    df = spark.read.csv(f"file://{filename}", header=True)

    # 转换湿度列为DecimalType
    df = df.withColumn('humidity', df['humidity'].cast(DecimalType(scale=1)))

    # 修正日期格式
    df = df.withColumn('time', F.to_timestamp(df['time'], "yyyy-MM-dd HH:mm"))

    df_humidity = df.select(
        df['province'],
        df['city_name'],
        df['humidity'],
        F.date_format(df['time'], "yyyy-MM-dd").alias("date"),
        F.hour(df['time']).alias("hour")
    ).filter((df['humidity'] <= 100) & (F.hour(df['time']).isin([2, 8, 12, 19])))

    df_4point_humidity = df_humidity.filter(df_humidity['hour'].isin([2, 8, 12, 19]))

    df_avg_humidity = df_4point_humidity.groupBy("province", "city_name", "date").agg(
        F.avg("humidity").alias("avg_humidity"),
        F.count("humidity").alias("count_humidity")
    ).filter("count_humidity == 4").sort("avg_humidity", ascending=False).select(
        "province", "city_name", "date", F.format_number('avg_humidity', 1).alias("avg_humidity")
    )

    df_avg_humidity.cache()

    # 写入CSV文件
    df_avg_humidity.coalesce(1).write.csv("file:///home/hadoop/exp/passed_humidity")

    print("end analysing passed humidity")

    avg_humidity_list = df_avg_humidity.limit(10).collect()
    return avg_humidity_list

result = passed_humidity_analyse("/usr/local/spark/weather1.csv")

