/*
* DESCRIPTION		:
* 	Create 4 arrays to compare
* 	Generate test data and check the search speed
* 	Record the search time and print it out on the screen through the stopwatch
*/
using System;
using System.Collections;
using System.Collections.Generic;
using System.Diagnostics;
using System.Dynamic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace a03
{
    internal class TestData
    {
        // Property
        public string[] DataSet { get; set; }
        public string[] StringArray { get; set; }
        public string[] SortedStringArray { get; set; }

        public Dictionary<string, string> DictionaryData = new Dictionary<string, string>();
        public Hashtable HashTableData = new Hashtable();
        public Stopwatch stopwatch = new Stopwatch();

        // Constructor
        public TestData()
        { }

        // Constructor
        public TestData(int maxNum)
        {
            List<string> list = new List<string>();
            /* Data is generated based on the received parameter value and put in each array */
            for (int i = 0; i < maxNum; i++)
            {
                Guid guid = Guid.NewGuid();
                list.Add(guid.ToString());
            }
            DataSet = list.ToArray();                               // DataSet
            StringArray = DataSet;                                  // String Array

            SortedStringArray = DataSet;                            // Sorted Array
            Array.Sort(SortedStringArray);

            foreach (string dstr in DataSet)
            {
                DictionaryData.Add(dstr, DateTime.Now.ToString());  // Dictionary
            }

            foreach (string hstr in DataSet)
            {
                HashTableData.Add(hstr, DateTime.Now.ToString());   // HashTable
            }
        }

        /*
         * Method       : GetRandomData()
         * Description  : Generate random data to perform a search
         * Parameters   : int count : Number of data
         * Return       : void
         */
        public void GetRandomData(int count)
        {
            string[] randTestData = new string[count];
            // Verify that the number of data to create is valid
            if (count < 0 || count > DataSet.Length)
            {
                Console.WriteLine("Search Data cannot set");
            }
            else
            {
                Random rand = new Random();
                // Randomly extract the data to be retrieved and pass it to the output method
                for (int i = 0; i < count; i++)
                {
                    randTestData[i] = DataSet[rand.Next(DataSet.Length)];
                }
                ShowTestSearch(randTestData);
            }
        }

        /*
         * Method       : GetInvalidData()
         * Description  : Generate invalid data
         * Parameters   : int count : Number of data
         * Return       : void
         */
        public void GetInvalidData(int count)
        {
            string[] invalidData = new string[count];
            List<string> invalidList = new List<string>();
            // Verify that the number of data to create is valid
            if (count < 0 || count > DataSet.Length)
            {
                Console.WriteLine("Search Data cannot set");
            }
            else
            {
                // Forward generated invalid data to the output method
                for (int i = 0; i < count; i++)
                {
                    Guid guid = Guid.NewGuid();
                    invalidList.Add(guid.ToString());
                }
                invalidData = invalidList.ToArray();
                ShowTestSearch(invalidData);
            }
        }

        /*
         * Method       : TestSearch()
         * Description  : Method for retrieving string array
         * Parameters   : string[] searchArr : Data to be retrieved
         * Return       : void
         */
        public void TestSearch(string[] searchArr)
        {
            for (int i = 0; i < searchArr.Length; i++)
            {
                StringArray.Contains(searchArr[i]);
            }
        }

        /*
        * Method       : TestSearch()
        * Description  : Method for retrieving sorted string array (BinarySearch)
        * Parameters   : string[] searchArr : Data to be retrieved
        * Return       : void
        */
        public void TestSearch(string[] strArr, string[] searchArr)
        {
            for (int i = 0; i < searchArr.Length; i++)
            {
                Array.BinarySearch(strArr, searchArr[i]);
            }
        }

        /*
        * Method       : TestSearch()
        * Description  : Method for retrieving dictionary
        * Parameters   : Dictionary<string, string> dArr : Dictionary to be scanned
        *                string[] searchArr              : Data to be retrieved
        * Return       : void
        */
        public void TestSearch(Dictionary<string, string> dArr, string[] searchArr)
        {
            for (int i = 0; i < searchArr.Length; i++)
            {
                dArr.ContainsKey(searchArr[i]);
            }
        }

        /*
        * Method       : TestSearch()
        * Description  : Method for retrieving hashtable
        * Parameters   : Hashtable hArr     : Hashtable to be scanned
        *                string[] searchArr : Data to be retrieved
        * Return       : void
        */
        public void TestSearch(Hashtable hArr, string[] searchArr)
        {
            for (int i = 0; i < searchArr.Length; i++)
            {
                hArr.ContainsKey(searchArr[i]);
            }
        }

        /*
         * Method       : ShowTestSearch()
         * Description  : A method that measures the search speed of each array and outputs it to the screen
         * Parameters   : string[] strArr : Data to be retrieved         
         * Return       : void
         */
        public void ShowTestSearch(string[] strArr)
        {
            stopwatch.Start();
            TestSearch(strArr);
            Console.WriteLine("String Array:        " + stopwatch.Elapsed.ToString());

            stopwatch.Restart();
            TestSearch(SortedStringArray, strArr);
            Console.WriteLine("Sorted String Array: " + stopwatch.Elapsed.ToString());

            stopwatch.Restart();
            TestSearch(DictionaryData, strArr);
            Console.WriteLine("Dictionary:          " + stopwatch.Elapsed.ToString());

            stopwatch.Restart();
            TestSearch(HashTableData, strArr);
            Console.WriteLine("HashTable:           " + stopwatch.Elapsed.ToString());
        }
    }
}
