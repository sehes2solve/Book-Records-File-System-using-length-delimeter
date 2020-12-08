#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

struct Book
{
    char ISBN[6];
    string title,author;
    float price;
    short year,pages_num;
};
void write_book(fstream& outfile,Book& b)
{
    outfile.put('$');
    outfile.write(b.ISBN,sizeof(b.ISBN));
    short len = b.title.size();
    outfile.write((char*)&len,sizeof(len));
    outfile.write(&b.title[0],len);
    len = b.author.size();
    outfile.write((char*)&len,sizeof(len));
    outfile.write(&b.author[0],len);
    outfile.write((char*)&b.price,sizeof(b.price));
    outfile.write((char*)&b.year,sizeof(b.year));
    outfile.write((char*)&b.pages_num,sizeof(b.pages_num));
}
void read_book(fstream& infile,Book& b)
{
    infile.get();
    infile.read(b.ISBN,sizeof(b.ISBN)/sizeof(char));
    short len;
    infile.read((char*)&len,sizeof(len));
    b.title.resize(len);
    infile.read(&b.title[0],len);
    infile.read((char*)&len,sizeof(len));
    b.author.resize(len);
    infile.read(&b.author[0],len);
    infile.read((char*)&b.price,sizeof(b.price));
    infile.read((char*)&b.year,sizeof(b.year));
    infile.read((char*)&b.pages_num,sizeof(b.pages_num));
}
istream& operator>>(istream& in,Book& b)
{
    cout << "Enter Book Data" << endl;
    cout << "Enter ISBN : " ;
    in >> b.ISBN ;
    cout << "Enter Title : " ;
    in.ignore();
    getline(in,b.title);//in >> b.title ;
    cout << "Enter Author : " ;
    getline(in,b.author);//in >> b.author ;
    cout << "Enter Price : " ;
    in >> b.price ;
    cout << "Enter Year : " ;
    in >> b.year ;
    cout << "Enter Number of pages : " ;
    in >> b.pages_num;
    return in;
}
ostream& operator<<(ostream& out,const Book& b)
{
    out << "ISBN : " << b.ISBN << "\nTitle : " << b.title << "\nAuthor : " << b.author << "\nPrice : " << b.price
    << "\nYear : " << b.year << "\nNumber of Pages : " << b.pages_num << endl;
    return out;
}
void add_book(fstream& outfile)
{
    Book temp;
    cin >> temp;
    outfile.seekp(0,ios::end);
    write_book(outfile,temp);
}
void print_all(fstream& infile)
{
    infile.seekg(0,ios::beg);
    Book temp;
    while(true)
    {
        read_book(infile,temp);
        if(infile.fail())
            break;
        cout << temp;
    }
}
void update_book(fstream& file,char ISBN[6],char* filename)
{
    fstream temp_file("temp.txt",ios::in|ios::out|ios::trunc);
    Book temp,book_update;
    cin >> book_update;
    file.seekg(0,ios::beg);
    while(true)
    {
        read_book(file,temp);
        if(file.fail())
            break;
        if(!strcmp(temp.ISBN,ISBN))
        {
            if(!(book_update.title.size() > temp.title.size() && book_update.author.size() > temp.author.size()))
            {
                string space;
                short larger_size = (temp.title.size() > temp.author.size())?temp.title.size():temp.author.size();
                for(int i = 0; i < larger_size;i++)
                    space += " ";
                file.put('$');

                file.write(book_update.ISBN,sizeof(book_update.ISBN));
                short len = temp.title.size();
                file.write((char*)&len,sizeof(len));
                file.write(&book_update.title[0],book_update.title.size());
                file.write(&space[0],len - book_update.title.size());
                len = temp.author.size();
                file.write((char*)&len,sizeof(len));
                file.write(&book_update.author[0],book_update.author.size());
                file.write(&space[0],len - book_update.author.size());
                file.write((char*)&temp.price,sizeof(temp.price));
                file.write((char*)&temp.year,sizeof(temp.year));
                file.write((char*)&temp.pages_num,sizeof(temp.pages_num));
            }
        }
        else
        {
            write_book(temp_file,temp);
        }
    }
    remove(filename);
    temp_file.close();
    rename("temp.txt",filename);
}

int main()
{

    fstream file("first try - Copy.txt",ios::in|ios::out|ios::app);
    update_book(file,"1012","first try - Copy.txt");




    return 0;
}
