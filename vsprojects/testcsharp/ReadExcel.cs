using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Reflection;
using System.Diagnostics;
using Excel = Microsoft.Office.Interop.Excel;


namespace testcsharp
{
    class ReadExcel
    {
        public string FileName;
                                           
        public void Read(string name)
        {
            Type officeType = Type.GetTypeFromProgID("Excel.Application");

            if (officeType == null)
            {
                // Excel is not installed.
                // Show message or alert that Excel is not installed.
                return;
            }

            // Excel is installed.
            // Let us continue our work on Excel file conversion. 
            Microsoft.Office.Interop.Excel.Application app = new Microsoft.Office.Interop.Excel.Application();

            try
            {
                // While saving, it asks for the user confirmation, whether we want to save or not.
                // By setting DisplayAlerts to false, we just skip this alert.
                app.DisplayAlerts = false;

                // Now we open the upload file in Excel Workbook. 
                Microsoft.Office.Interop.Excel.Workbook excelWorkbook = app.Workbooks.Open(name);

                //string newFileName = System.IO.Directory.GetCurrentDirectory() + "\\DataMigration.csv";
                string newFileName = name + ".csv";

                // Now save this file as CSV file.
                excelWorkbook.SaveAs(newFileName, Microsoft.Office.Interop.Excel.XlFileFormat.xlCSV);

                // Close the Workbook and Quit the Excel Application at the end. 
                excelWorkbook.Close();
            }
            catch (System.Exception ex)
            {
                Console.WriteLine(ex.Message);
            }
            finally
            {
                app.Quit();
            }
        }

        public void Display()
        {

        }
    }
}
