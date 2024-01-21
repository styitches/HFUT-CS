from pyspark.sql import SparkSession
from pyspark.sql.functions import col, sum, desc
from pyspark.sql.types import DecimalType


def passed_rain(filename):
    print("Begin to analyze passed rain")

    spark = SparkSession.builder.master("local").appName("passed_rain_analyse").getOrCreate()

    # 读取CSV文件
    df = spark.read.csv(f"file://{filename}", header=True)

    # 选择相关列并转换雨量数据类型
    df_rain = df.select(col('province'), col('city_name'), col('rain1h').cast(DecimalType(scale=1))).filter(col('rain1h') < 1000)  # 筛选数据，去除无效数据

    # 分组、求和、排序
    df_rain_sum = df_rain.groupBy("province", "city_name").agg(sum("rain1h").alias("rain24h")).sort(desc("rain24h"))

    # 缓存数据
    df_rain_sum.cache()

    # 将结果写入CSV文件
    df_rain_sum.coalesce(1).write.csv("file:///home/hadoop/exp/passed_rain")

    print("End analyzing passed rain")

    # 返回前20行结果
    return df_rain_sum.head(20)
result = passed_rain("/usr/local/spark/weather1.csv")

