from pyspark.sql import SparkSession
from pyspark.sql.functions import col, date_format, hour, avg, count, format_number

def passed_pressure(filename):
    print("begin to analyse passed pressure")
    
    # 1. 创建SparkSession
    spark = SparkSession.builder.master("local").appName("passed_pressure_analyse").getOrCreate()
    
    # 2. 读取CSV文件
    df = spark.read.csv(f"file://{filename}", header=True)
    
    # 3. 选择需要的列
    df_pressure = df.select(
        col('province'),
        col('city_name'),
        col('pressure').cast('double'),  # 将气压列转换为double类型
        date_format(col('time'), "yyyy-MM-dd").alias("date"),
        hour(col('time')).alias("hour")
    )
    
    # 4. 过滤气压大于1300的数据
    df_filtered_pressure = df_pressure.filter(df_pressure['pressure'] <= 1300)
    
    # 5. 过滤保留指定小时的数据
    df_4point_pressure = df_filtered_pressure.filter(df_filtered_pressure['hour'].isin([2, 8, 12, 19]))
    
    # 6. 气压统计分析
    df_avg_pressure = df_4point_pressure.groupBy("province", "city_name", "date").agg(avg("pressure").alias("avg_pressure")).filter(count("pressure") == 4).sort(col("avg_pressure")).select("province", "city_name", "date", format_number('avg_pressure', 1).alias("avg_pressure"))
    
    # 7. 缓存DataFrame
    df_avg_pressure.cache()
    
    # 8. 将结果写入csv文件
    df_avg_pressure.coalesce(1).write.csv("file:///home/hadoop/exp/passed_pressure")
    
    print("end analysing passed pressure")
    
    # 9. 返回前10行结果
    avg_pressure_list = df_avg_pressure.limit(10).collect()
    return avg_pressure_list

result = passed_pressure("/usr/local/spark/weather1.csv")

