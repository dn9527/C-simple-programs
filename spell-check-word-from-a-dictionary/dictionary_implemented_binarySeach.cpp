//Dat Nguyen
//Computer Science Student at De Anza College
//This program reads in a txt file of words
//sorts in ascending order
//and implements binary search for finding words
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

using namespace std;

void check_infile(ifstream&, string);
void check_outfile(ofstream&, string);
void read_input(ifstream&, string [], int);
void bubble_sort(string [], int);
void swap(string&, string& );
void search(ofstream&, string [], string [], int, int, int&);

int main()
{
    string dictionary[16000];
    string keywords[84];
    string inpath_dictionary, inpath_keywords, outpath_report;
    int size_dictionary = sizeof(dictionary)/sizeof(string);
    int size_keywords = sizeof(keywords)/sizeof(string);
    int count =0;
    cout << "\nWelcome to assignment #2\n"
         << "\nPlease enter full pathname of the dictionary file (including .txt): ";
    getline(cin, inpath_dictionary); //cin.ignore();
    ifstream in_dictionary(inpath_dictionary.c_str());
    check_infile(in_dictionary, inpath_dictionary);

    cout << "\nPlease enter full pathname of the keywords file (including .txt): ";
    getline(cin, inpath_keywords);
    ifstream in_keywords(inpath_keywords.c_str());
    check_infile(in_keywords, inpath_keywords);

    cout << "\nGetting data..\n..\n..\n" << endl;
    read_input(in_dictionary, dictionary, size_dictionary);
    read_input(in_keywords, keywords, size_keywords);

    in_dictionary.close();
    in_keywords.close();

    cout << "It takes a while to sort the data. Please wait..\n" << endl;
    bubble_sort(dictionary, size_dictionary);
    bubble_sort(keywords, size_keywords);
    cout << "Data has been sorted\n\n";

    cout << "Please enter full pathname of the output file (including .txt): ";
    getline(cin, outpath_report);
    ofstream out_report(outpath_report.c_str());
    check_outfile(out_report, outpath_report);


    cout << "\nSearching keywords.." << endl;

    search(out_report, keywords, dictionary, size_keywords, size_dictionary, count);
    out_report.close();
    cout << "Number of keywords not found: " << count << endl << endl
         << "Please open " << outpath_report << " to see the report\n";
}


void check_infile(ifstream& file, string path)
{
    if(!file)
    {
        cerr << "Sorry, can't open the input file " << path
             << "\nPress enter to stop the program" << endl;
        exit(1);
    }
}

void check_outfile(ofstream& file, string path)
{
    if(!file)
    {
        cerr << "Sorry, can't create the output file " << path
             << "\nPress enter to stop the program" << endl;
        exit(2);
    }
}

void read_input(ifstream& read, string a[], int n)
{
    for(int i=0; i<n; i++)
    {
        read >> a[i];
    }
}

void bubble_sort(string a[], int n)
{
    bool do_swapping;
    do
    {
        do_swapping = false;
        for(int i=0; i< n-1; i++)
        {
            if(a[i] > a[i+1])
            {
                swap(a[i], a[i+1]);
                do_swapping = true;
            }
        }
    }
    while(do_swapping == true);

}

void swap(string& a, string& b)
{
    string temp;
    temp = a;
    a = b;
    b=temp;
}

void search(ofstream& write, string k[], string d[], int n1, int n2, int& c)
{
    bool found;
    for(int i=0; i< n1; i++)
    {
        int low, high, mid;
        low = 0;
        high = n2-1;
        found = false;

        while (low <= high && found == false)
        {
            mid = (low + high)/ 2;
            if (k[i] < d[mid])
            {
                high = mid-1;
            }
            else if (k[i] > d[mid])
            {
                low = mid+1;
            }
            else
            {
                found = true;
            }
        }

        if(found == false)
        {
            c++;
            write << "Keyword not found: " << k[i] << endl;
        }
    }
}
