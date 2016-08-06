using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Globalization;

namespace testcsharp
{

    class Program
    {
        static string GetDateTimeString(string t, string format)
        {
            DateTime dt;
            if (DateTime.TryParseExact(t, format, System.Globalization.CultureInfo.GetCultureInfo("en-US"), System.Globalization.DateTimeStyles.None, out dt))
            {
                DateTime now = DateTime.Now;
                if (dt.Year == now.Year && dt.Day == now.Day)
                {
                    //return dt.ToShortTimeString();
                    return dt.ToString("HH时mm分ss秒");
                }
                else
                {
                    //return dt.ToLongDateString();
                    return dt.ToString("yyyy年MM月dd日");
                }
            }
            return t;
        }

        static void test_GetDateTimeString()
        {
            System.Console.WriteLine(GetDateTimeString("151103112030", "yyMMddHHmmss"));
            System.Console.WriteLine(GetDateTimeString("151102112030", "yyMMddHHmmss"));
            System.Console.WriteLine(GetDateTimeString("20151106", "yyyyMMdd"));
            System.Console.WriteLine(GetDateTimeString("20151102", "yyyyMMdd"));
            System.Console.ReadKey();              
        }

        static void Main(string[] args)
        {
            ReadExcel readExcel = new ReadExcel();
            readExcel.Read("c:/123/test.xlsx");
        }


    }
}
