#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
using namespace std;

//
struct BookInfo
{
    string book;
    int price;
    int pages;
    double rating;
    void Out();
};

//Двусвязный список 
struct DLList
{
    struct Node
    {
        BookInfo data;     //information
        Node* next;   //next node position
        Node* prev;   //previous node position
    };

    Node* F = NULL;     //first node
    Node* L = NULL;     //last node
    Node* C = NULL;     //current node
    int Count;        //node count

    void Out();
    void Info();
    void Clear();

    bool MoveNext();
    bool MovePrev();
    bool MoveFirst();
    bool MoveLast();

    bool Init(BookInfo);
    bool AddNext(BookInfo);
    bool AddPrev(BookInfo);
    bool AddFirst(BookInfo);
    bool AddLast(BookInfo);

    bool Del(BookInfo&);
    bool DelNext(BookInfo&);
    bool DelPrev(BookInfo&);
    bool DelFirst(BookInfo&);
    bool DelLast(BookInfo&);
};

//От текущиго узла вперед на одно 
bool DLList::MoveNext()
{
    //Это все было в лекции 
    if (!F)       return false;
    if (!C) { C = F; return true; }
    if (!C->next) return false;
    C = C->next;
    return true;
}

//От текущего узла назад  
bool DLList::MovePrev()
{
    if (!F)       return false;
    if (!C) { C = F; return true; }
    if (!C->prev) return false;
    C = C->prev;
    return true;
}

//Перейти на первый узел 
bool DLList::MoveFirst()
{
    if (!F) return false;
    C = F;
    return true;
}

//Перейти на поседний 
bool DLList::MoveLast()
{
    if (!L) return false;
    C = L;
    return true;
}


//Иницализация узла
bool DLList::Init(BookInfo data)
{
    if (!F)
    {
        F = new Node;
        L = F;
        C = F;
        F->prev = NULL;
        F->next = NULL;
        F->data = data;
        Count = 1;
        return true;
    }
    else
        return false;
}

//Добавить узел на след позицию от текущей
bool DLList::AddNext(BookInfo data)
{
    if (!F) return Init(data);

    Node* temp = C->next;
    C->next = new Node;
    C->next->next = temp;
    C->next->prev = C;

    if (!temp)
        L = C->next;
    else
        temp->prev = C->next;

    C = C->next;
    C->data = data;
    Count++;
    return true;

}

//Добавить узел на предыдущую позицию от текущей
bool DLList::AddPrev(BookInfo data)
{
    if (!F) return Init(data);

    Node* temp = C->prev;
    C->prev = new Node;
    C->prev->next = C;
    C->prev->prev = temp;

    if (!temp)
        F = C->prev;
    else
        temp->next = C->prev;

    C = C->prev;
    C->data = data;
    Count++;
    return true;
}


//Добавить узел в начало
bool DLList::AddFirst(BookInfo data)
{
    if (MoveFirst())return AddPrev(data);
    else return false;
}

//Добавить узел в конец 
bool DLList::AddLast(BookInfo data)
{
    if (MoveLast())return AddNext(data);
    else return false;
}

//Вывод каждого узла
void DLList::Out()
{
    if (!F)
    {
        cout << "Список пуст" << endl;
        return;
    }

    Node* temp = F;
    cout << "Список: " << endl << endl;
    do
    {
        temp->data.Out();
        temp = temp->next;
    } while (temp);
    cout << endl;
}

//Кол-во узлов и текущий узел
void DLList::Info()
{

    if (Count)
        cout << "Количество узлов списка: "
        << Count << endl << endl;
    else
        cout << "Список пуст" << endl;
    if (C)
    {
        if (MoveFirst())
        {
            cout << "Текущие данные узла: ";
            C->data.Out();
        }
    }
}

//Удалить первый узел
bool DLList::DelFirst(BookInfo& data)
{
    if (!F)      return false;
    if (C != F)    MoveFirst();

    Node* temp = C->next;
    data = C->data;

    if (temp) temp->prev = NULL;
    delete C;

    C = temp;
    F = temp;
    Count--;
    if (!temp) { L = NULL; return false; }
    return true;
}

//Удалить последний узел
bool DLList::DelLast(BookInfo& data)
{
    if (!F)      return false;
    if (C != L)    MoveLast();

    Node* temp = C->prev;
    data = C->data;

    if (temp) temp->next = NULL;
    delete C;

    C = temp;
    L = temp;
    Count--;

    if (!temp) { F = NULL; return false; }
    return true;
}

//Удалить все 
bool DLList::Del(BookInfo& data)
{
    if (!F) return false;
    if (!C) return false;

    if (C == F) return DelFirst(data);
    if (C == L) return DelLast(data);

    Node* temp = C->next;
    data = C->data;

    C->prev->next = C->next;
    C->next->prev = C->prev;

    delete C;
    C = temp;
    Count--;
    return true;
}

//Удалить следующий узел
bool DLList::DelNext(BookInfo& data)
{
    if (!F) return false;
    if (!C) return false;
    if (MoveNext()) return Del(data);
    return false;
}

//Удалить предыдущий узел
bool DLList::DelPrev(BookInfo& data)
{
    if (!F) return false;
    if (!C) return false;
    if (MovePrev()) return Del(data);
    return false;
}

//Чистка
void DLList::Clear()
{
    if (!MoveFirst())
    {
        cout << "Список пуст!" << endl;
        return;
    }
    BookInfo k;
    while (Del(k));
}

void BookInfo::Out()
{
    cout << "Книга: " << book << "\t\t" << "Цена: " << price << "\t" << "Страницы: " << pages << "\t" << "Рейтинг: " << rating << endl << endl;
}

bool GetFile(DLList&, BookInfo&);
bool WriteFile(DLList&, BookInfo&);
void GetBook(BookInfo&);

int main()
{
    setlocale (LC_ALL,"RUS");
    BookInfo Info;
    DLList DLList;
    GetFile(DLList, Info);
    DLList.Out();
    int num, key = 0, key1 = 0, key2 = 0;
    do
    {
        cout << "1) Добавить элемент" << endl
            << "2) Удалить элемент" << endl
            << "3) Очистить список" << endl
            << "4) Обновить данные" << endl
            << "0) Выход" << endl;
        cout << endl << "Выбирит действие: ";
        cin >> key;
        cout << endl;
        switch (key)
        {
        case 1:
            cout << "1) Добавить в начало" << endl
                << "2) Добавить в конец" << endl
                << "3) Добавить в К-ую позицию" << endl
                << "0) Назад" << endl;
            cout << endl << "Выбирите действие: ";
            cin >> key1;
            cout << endl;
            switch (key1)
            {
            case 1:
                GetBook(Info);
                DLList.AddFirst(Info);
                DLList.Out();
                break;
            case 2:
                GetBook(Info);
                DLList.AddLast(Info);
                DLList.Out();
                break;
            case 3:
                cout << "Введите позицию: ";
                cin >> num;
                GetBook(Info);
                if (num == 1)//Если num равна первому узлу
                {
                    DLList.AddFirst(Info);
                    DLList.Out();
                    break;
                }
                else if (num == DLList.Count + 1)//Если num равна конечному узлу
                {
                    DLList.AddLast(Info);//Добавить узел в конец
                    DLList.Out();//Вывод каждого узла
                    break;
                }
                DLList.MoveFirst();//Перейти на первый узел
                for (int i = 1; i < num - 1; i++)
                {
                    DLList.MoveNext();//Перейти на следующий узел
                }
                DLList.AddNext(Info);//Добавить узел на след позицию от текущей
                DLList.Out();
                break;
            default:
                if (key1 != 0)
                {
                    cout << "Такого действия нет !" << endl << endl;
                }
                break;
            }
            break;
        case 2:
            cout << "1) Удалить первый элемент" << endl
                << "2) Удалить последний элемент" << endl
                << "3) Удалить К-ую позицию" << endl
                << "0) Назад" << endl;
            cout << endl << "Выбирите действие: ";
            cin >> key2;
            cout << endl;
            switch (key2)
            {
            case 1:
                DLList.DelFirst(Info);
                DLList.Out();
                break;
            case 2:
                DLList.DelLast(Info);
                DLList.Out();
                break;
            case 3:
                cout << "Введите позицию: ";
                cin >> num;
                if (num == 1)
                {
                    DLList.DelFirst(Info);
                    DLList.Out();
                    break;
                }
                else if (num == DLList.Count)
                {
                    DLList.DelLast(Info);
                    DLList.Out();
                    break;
                }
                DLList.MoveFirst();
                for (int i = 1; i < num; i++)
                {
                    DLList.MoveNext();
                }
                DLList.Del(Info);
                DLList.Out();
                break;
            default:
                if (key2 != 0)
                {
                    cout << "Такого действия нет!" << endl << endl;
                }
                break;
            }
            break;
        case 3:
            DLList.Clear();
            DLList.Out();
            break;
        case 4:
            WriteFile(DLList, Info);
            break;
        default:
            if (key != 0)
            {
                cout << "Такого действия нет!" << endl << endl;
            }
            DLList.Clear();
            DLList.Out();
            break;
        }
    } while (key != 0);
}

bool GetFile(DLList& DLList, BookInfo& Info)
{
    ifstream F("Books.txt");
    if (!F)
    {
        cout << "Файл не обнаружен" << endl;
        return false;
    }
    while (F >> Info.book >> Info.price >> Info.pages >> Info.rating)
    {
        DLList.AddNext(Info);
    }
    F.close();
    return true;
}

bool WriteFile(DLList& DLList, BookInfo& Info)
{
    ofstream F("Books.txt");
    if (!F)
    {
        cout << "Файл не обнаружен" << endl;
        return false;
    }
    DLList.MoveFirst();
    do
    {
        F << DLList.C->data.book << " " << DLList.C->data.pages << " " << DLList.C->data.price << " " << DLList.C->data.rating << endl;
    } while (DLList.MoveNext());
    DLList.MoveFirst();
    F.close();
    return true;
}

void GetBook(BookInfo& Info)
{
    cout << "Введите название: ";
    cin >> Info.book;
    cout << endl;
    cout << "Введите цену: ";
    cin >> Info.price;
    cout << endl;
    cout << "Введите кол-во страниц: ";
    cin >> Info.pages;
    cout << endl;
    cout << "Введите рейтинг: ";
    cin >> Info.rating;
    cout << endl;
}