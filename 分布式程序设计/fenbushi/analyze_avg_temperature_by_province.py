from pyspark.sql import SparkSession
from pyspark.sql.functions import col, avg, format_number

def analyze_avg_temperature_by_province(filename):
    print("Begin average temperature analysis by province")

    # 创建SparkSession
    spark = SparkSession.builder.master("local").appName("avg_temperature_analysis").getOrCreate()

    # 读取CSV文件
    df = spark.read.csv(f"file://{filename}", header=True)

    # 选择需要的列
    df_temperature = df.select(
        col('province'),
        col('temperature').cast('double')
    )

    # 过滤异常值
    df_filtered_temperature = df_temperature.filter(
        (df_temperature['temperature'] >= -50) & (df_temperature['temperature'] <= 50)
    )

    # 平均气温统计分析
    df_avg_temperature = df_filtered_temperature.groupBy("province").agg(avg("temperature").alias("avg_temperature")).sort(col("avg_temperature"), ascending=False)

    # 缓存DataFrame
    df_avg_temperature.cache()

    # 将结果写入csv文件
    df_avg_temperature.coalesce(1).write.csv("file:///home/hadoop/exp/avg_temperature_by_province")

    # 打印结果
    df_avg_temperature.show(truncate=False)

    print("End average temperature analysis by province")

    # 返回结果
    avg_temperature_list = df_avg_temperature.collect()
    return avg_temperature_list

# 示例：统计各个省的平均气温
result_avg_temperature_by_province = analyze_avg_temperature_by_province("/usr/local/spark/weather1.csv")

