 ## Работа с файлове
 - файл - последователност от байтове
 - можем да отворим поток за вход/изход към файл
 - работим по същия начин, както със std::cin/std::cout
```cpp
#include <iostream>
#include <fstream>

constexpr int BUFF_SIZE = 1024;
const char FILE_NAME[] = "data.txt";

int main()
{
	std::ifstream inFile(FILE_NAME);

	if (!inFile.is_open()) {
		std::cout << "Error opening file!" << std::endl;
		return -1;
	}
	
	while (!inFile.eof()) {
        // можем да прочетем целия ред/до разделител
		char buff[BUFF_SIZE];
		inFile.getline(buff, BUFF_SIZE);
		
        //алтернативно, можен=м да прочетем само един символ
        char c = inFile.get();

        //или
        int a, b;
        inFile >> a >> b;

		//обработваме прочетения ред
	}

	
	inFile.close();
}
```

 ```c++
#include <iostream>
#include <fstream>

const char FILE_NAME[] = "data.txt";

int main()
{
	std::ofstream outFile(FILE_NAME);  

	if (!outFile.is_open()) {
		std::cout << "Error opening file!" << std::endl;
		return -1;
	}
	
	int a = 5;
    char b[] = "str";

	outFile << a << " " << b << std::endl;

    //алтернативно, можем да запишем 1 символ
    outFile.put(b[0]);

	outFile.close();
}
 ```

## Позициониране във файл
### **get указател** - указател на istream/ifstream, реферира следващия елемент, който ще се прочете от потока
- **tellg()** - връща позицития на get указателя
- **seekg(offset, direction)** - премества get-указателят на конкретна позцития, където

    -> **offset** - отместването от direction (цяло число)
    
    -> **direction** - едно от следните:
    1. ios::beg - началото на файла
    2. ios::cur - текущата позиция във файла
    3. ios::end - края на файла

 - **seekg(streampos idx)** - премества get-указателя на позция idx (започвайки от 0)
### **put указател** - указател на ostream/ofstream, реферира мястото в паметта, където ще се запише следващият елемент

 - **tellp()** - wръща позицития на put указателя

 - **seekp(offset, direction)** - премества put-указателя на конкретна позцития
 - **seekp(streampos idx)** - премества put-указателят на позция idx
