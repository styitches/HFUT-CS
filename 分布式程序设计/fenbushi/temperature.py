from pyspark.sql import SparkSession
from pyspark.sql.functions import col, date_format, hour, avg, count, format_number
from pyspark.sql.types import DecimalType

def passed_temperature(filename):
    print("begin to analyse passed temperature")
    
    # 1. 创建SparkSession
    spark = SparkSession.builder.master("local").appName("passed_temperature_analyse").getOrCreate()
    
    # 2. 读取CSV文件
    df = spark.read.csv(f"file://{filename}", header=True)
    
    # 3. 选择需要的列
    df_temperature = df.select(
        col('province'),
        col('city_name'),
        col('temperature').cast(DecimalType(scale=1)),
        date_format(col('time'), "yyyy-MM-dd").alias("date"),
        hour(col('time')).alias("hour")
    )
    
    # 4. 过滤保留指定小时的数据
    df_4point_temperature = df_temperature.filter(df_temperature['hour'].isin([2, 8, 12, 19]))
    
    # 5. 温度统计分析
    df_avg_temperature = df_4point_temperature.groupBy("province", "city_name", "date").agg(avg("temperature").alias("avg_temperature")).filter(count("temperature") == 4).sort(col("avg_temperature")).select("province", "city_name", "date", format_number('avg_temperature', 1).alias("avg_temperature"))
    
    # 6. 缓存DataFrame
    df_avg_temperature.cache()
    
    # 7. 将结果写入CSV文件
    df_avg_temperature.coalesce(1).write.csv("file:///home/hadoop/exp/passed_temperature")
    
    print("end analysing passed temperature")
    
    # 8. 返回前10行结果
    avg_temperature_list = df_avg_temperature.limit(10).collect()
    return avg_temperature_list
result = passed_temperature("/usr/local/spark/weather1.csv")
