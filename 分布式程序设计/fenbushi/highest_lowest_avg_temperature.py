from pyspark.sql import SparkSession
from pyspark.sql.functions import col, date_format, hour, avg, count, format_number

def highest_lowest_avg_temperature(filename, is_highest=True):
    print("begin to analyze past 24 hours average temperature")
    
    # 1. 创建SparkSession
    spark = SparkSession.builder.master("local").appName("temperature_analysis").getOrCreate()
    
    # 2. 读取CSV文件
    df = spark.read.csv(f"file://{filename}", header=True)
    
    # 3. 选择需要的列
    df_temperature = df.select(
        col('province'),
        col('city_name'),
        col('temperature').cast('double'),
        date_format(col('time'), "yyyy-MM-dd").alias("date"),
        hour(col('time')).alias("hour")
    )
    
    # 4. 过滤保留过去24小时的数据，并排除异常值
    df_24hours_temperature = df_temperature.filter(
        (df_temperature['hour'] >= 2) & (df_temperature['hour'] <= 19) &
        (df_temperature['temperature'] >= -50) & (df_temperature['temperature'] <= 50)
    )
    
    # 5. 气温统计分析
    df_avg_temperature = df_24hours_temperature.groupBy("province", "city_name").agg(avg("temperature").alias("avg_temperature")).sort(col("avg_temperature"), ascending=not is_highest).limit(20)
    
    # 6. 缓存DataFrame
    df_avg_temperature.cache()
    
    # 7. 打印结果
    df_avg_temperature.coalesce(1).write.csv("file:///home/hadoop/exp/highest_avg_temperature")
    
    print("end analyzing past 24 hours average temperature")
    
    # 8. 返回结果
    avg_temperature_list = df_avg_temperature.collect()
    return avg_temperature_list

# 示例：统计过去24小时全国平均气温最高的20座城市，排除异常值
result_highest_temperature = highest_lowest_avg_temperature("/usr/local/spark/weather1.csv", is_highest=True)

