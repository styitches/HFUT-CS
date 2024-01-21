from pyspark.sql import SparkSession
from pyspark.sql.functions import col, avg, format_number

def analyze_avg_rainfall_by_province(filename):
    print("Begin average rainfall analysis by province")

    # 创建SparkSession
    spark = SparkSession.builder.master("local").appName("avg_rainfall_analysis").getOrCreate()

    # 读取CSV文件
    df = spark.read.csv(f"file://{filename}", header=True)

    # 选择需要的列
    df_rainfall = df.select(
        col('province'),
        col('rain1h').cast('double')
    )

    # 过滤异常值
    df_filtered_rainfall = df_rainfall.filter(
        (df_rainfall['rain1h'] >= 0) & (df_rainfall['rain1h'] <= 200)
    )

    # 平均降雨量统计分析
    df_avg_rainfall = df_filtered_rainfall.groupBy("province").agg(avg("rain1h").alias("avg_rainfall")).sort(col("avg_rainfall"), ascending=False)

    # 缓存DataFrame
    df_avg_rainfall.cache()

    # 将结果写入csv文件
    df_avg_rainfall.coalesce(1).write.csv("file:///home/hadoop/exp/avg_rainfall_by_province")

    # 打印结果
    df_avg_rainfall.show(truncate=False)

    print("End average rainfall analysis by province")

    # 返回结果
    avg_rainfall_list = df_avg_rainfall.collect()
    return avg_rainfall_list

# 示例：统计各个省的平均降雨量
result_avg_rainfall_by_province = analyze_avg_rainfall_by_province("/usr/local/spark/weather1.csv")

