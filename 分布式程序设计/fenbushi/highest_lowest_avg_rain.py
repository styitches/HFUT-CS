from pyspark.sql import SparkSession
from pyspark.sql.functions import col, date_format, hour, avg, count, format_number

def highest_lowest_avg_rainfall(filename, is_highest=True):
    print("begin to analyze past 24 hours average rainfall")
    
    # 1. 创建SparkSession
    spark = SparkSession.builder.master("local").appName("rainfall_analysis").getOrCreate()
    
    # 2. 读取CSV文件
    df = spark.read.csv(f"file://{filename}", header=True)
    
    # 3. 选择需要的列
    df_rainfall = df.select(
        col('province'),
        col('city_name'),
        col('rain1h').cast('double'),
        date_format(col('time'), "yyyy-MM-dd").alias("date"),
        hour(col('time')).alias("hour")
    )
    
    # 4. 过滤保留过去24小时的数据，并排除异常值
    df_24hours_rainfall = df_rainfall.filter(
        (df_rainfall['hour'] >= 2) & (df_rainfall['hour'] <= 19) &
        (df_rainfall['rain1h'] >= 0) & (df_rainfall['rain1h'] <= 200)
    )
    
    # 5. 降水量统计分析
    df_avg_rainfall = df_24hours_rainfall.groupBy("province", "city_name").agg(avg("rain1h").alias("avg_rainfall")).sort(col("avg_rainfall"), ascending=not is_highest).limit(20)
    
    # 6. 缓存DataFrame
    df_avg_rainfall.cache()
    
    # 7. 打印结果
    df_avg_rainfall.coalesce(1).write.csv("file:///home/hadoop/exp/highest_avg_rainfall")
    print("end analyzing past 24 hours average rainfall")
    
    # 8. 返回结果
    avg_rainfall_list = df_avg_rainfall.collect()
    return avg_rainfall_list

# 示例：统计过去24小时全国平均降水量最高的20座城市，排除异常值
result_highest_rainfall = highest_lowest_avg_rainfall("/usr/local/spark/weather1.csv", is_highest=True)

