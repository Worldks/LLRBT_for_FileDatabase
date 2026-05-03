# Overview  
The program implements a simple file database that supports adding records,
displaying their values, and displaying the database contents. The database is a table with two fields:
a string (60 characters long) and an integer (the number of times the string has been inserted into the database).
The database is a key-value data structure.
The data structure is based on a left-hand red-black tree according to [Sedgwick](https://www.youtube.com/live/JHitk1lq-NM?si=UhsPIxyAXz1HErtN).
The data structure itself is located in a file on disk, not in RAM,
therefore, offsets relative to the beginning of the file serve as pointers to tree nodes.
Supported operations:  
> search by key  
> add new key  
 
Программа реаизует простую файловую базу данных поддерживающию добавление записей,  
вывод их значений и вывод содержимого базы. База представляет собой таблицу из двух полей:  
строка(длина 60 символов) и целого числа (количество вставок строки в базу).  
База представлет собой структуру данных ключ-значение.  
Структура данных реализована на основе левостороннего красно-черного дерева по [Седжвику](https://www.youtube.com/live/JHitk1lq-NM?si=UhsPIxyAXz1HErtN).  
Сама структура данных располагается в файле на диске, а не в ОЗУ,
поэтому в качестве указателей на узлы дерева служат смещения относительно начала файла.  
Поддерживаемые операции:
> поиск по ключу  
> добавление нового ключа  

#  Build  
В директории build  
>make prog  

# Usage  
The build directory contains a pre-prepared database with unique entries.

You can use it to test the program or create your own database with unique keys.

*Adding an entry to the database*  
>./prog db_2000 add user2001  

*Display all database contents*  
>./prog db_2000 list

That is, add, query, list - operations supported by the database on its instance (db_2000).  

В директории build есть подготовленная база с уникальными записями,  
её можно использовать для тестрирования работы программы или создать свою базу с уникальными ключами.  
*Добавление записи в базу*  

>./prog db_2000 add user2001  

*Количество добавлений записи в базу*  

>./prog db_2000 query user2001  

*Вывод всего содержимого базы*  

>./prog db_2000 list  

Т.е. add, query, list - операции поддерживаемы базой данных над её экземпляром (db_2000).
