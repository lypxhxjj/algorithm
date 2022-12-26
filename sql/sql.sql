-- 如何获取当天分区，p_day的那个。
select 
    count(1) 
from 
    ods.ods_xxx
where 
    p_day = CAST(FORMAT_DATETIME(CURRENT_DATE - INTERVAL '0' DAY, 'yyyyMMdd') AS VARCHAR) 
    and course_id = 1


-- 类型转换如何操作：cast(body['user_id'] AS BIGINT)
-- user_id 不在xxx，not in + 子查询语句，子查询中使用distinct。
select count(1)
from 
    ods.xxx
where 
    p_day = CAST(FORMAT_DATETIME(CURRENT_DATE - INTERVAL '1' DAY, 'yyyyMMdd') AS VARCHAR)
    and user_id not in (
        select distinct(cast(body['user_id'] AS BIGINT))
        from 
            dwd.xxx
        where   
            service = 'xxx'
            and p_day >= CAST(FORMAT_DATETIME(CURRENT_DATE - INTERVAL '7' DAY, 'yyyyMMdd') AS VARCHAR)     
    )


-- 两天的数据差集：id not in (子查询)
-- 注意：数据差集只是记录新增级别的，记录的修改是检测不到的。
select count(1)
from 
    ods.ods_xxx
where 
    p_day = CAST(FORMAT_DATETIME(CURRENT_DATE - INTERVAL '1' DAY, 'yyyyMMdd') AS VARCHAR)
    and user_id not in (
        select distinct(user_id)
        from 
            ods.ods_xxx
        where 
            p_day = CAST(FORMAT_DATETIME(CURRENT_DATE - INTERVAL '1' DAY, 'yyyyMMdd') AS VARCHAR) 
            and id not in (
                select id 
                from 
                    ods.ods_xxx
                where 
                    p_day = CAST(FORMAT_DATETIME(CURRENT_DATE - INTERVAL '8' DAY, 'yyyyMMdd') AS VARCHAR)
        )
    )


-- 如何保留两位小数的除法：*1.00
-- 二层group by
select p_day, (count(*) * 1.00/count(distinct(user_id))) as "日均"
from (
  select p_day, body['user_id'] as user_id, body['lecture_id'] as lecture_id 
  from
    dwd.dwd_xxx
  where   
    and p_day >= '20221120'
    group by p_day,body['user_id'],body['lecture_id']
  ) 
group by p_day
order by p_day desc