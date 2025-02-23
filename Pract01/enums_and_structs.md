# Енумерации и структури в C++

## Енумерации
Енумерациите представляват тип данни, които са рестриктирани до определен домейн от стойности, включващ специално дефинирани константи.

Разграничаваме 2 типа енумерации - `enum` и `enum class`. 

Ето и сравнение между тях:
- Преобразуване към други типове:
    - `enum`: Членовете се преобразуват неявно към int по default, или към типа данни, който е зададен.
    - `enum class`: няма неявни преобразувания.

    ```c++
        enum Color
        {
            RED, 
            BLUE, 
            GREEN
        };

        enum class Fruit
        {
            ORANGE, 
            BLUEBERRY
        };
    
        int main()
        {
            Color c = RED;
            if(c == 0)
            {
                //do something...
            }

	    Fruit f = Fruit::ORANGE;
            if(f == 0) // error
            { ... }
        }
    ```
> [!IMPORTANT]
> Такива преобразувания водят до писане на трудно четим и неразбираем код!

- Обхват:
    - `enum`: *unscoped*, членовете му (константите) се декларират в глобалното пространство.
    - `enum class`: *scoped*, членовете се достъпват чрез scope resolution-оператора:
  ```
     enum_class_name::something.
  ```
Пример: 

     ```c++
        enum class Animal
        {
            DOG, 
            CAT,
            MOUSE
        }

        int main()
        {
            Animal::DOG;
            // just DOG won`t work
        }
     ```

- Дефиниране на конкретни стойности:
    - И в двата случая може да се задават конкретни стойности.

    ```c++
        enum Status {
            Ok = 200,
            NotFound = 404
        };

        enum class HttpStatus {
            Ok = 200,
            NotFound = 404
        };
    ```

## Структури
Структурите представляват последователност от полета, които са записани в определен ред в паметта.

```c++
    struct Date
    {
        int day = 1; // default value
        int month = 1;
        int year = 2000;
    };

    void foo1(Date d)
    {
        d.day = -1; // we don`t change the valude of d.day because a copy of the struct is given as a parameter to the function foo1.
    }

    void foo2(Date& d)
    {
        d.day = 20; // here we change the value of d`s day because a reference to the instance is given to foo2.
    }

    int main()
    {
        Day d; // we create an instance of Day with default values
        Day d2 = { 12, 1, 1995 }; // we create instance of Day with custom values
        
        std::cout << d.day << '\n'; // we acces the data of the instance by usinf operator .

        foo1(d); // still default values as we do not change anything

        foo2(d) // day is now 20, month = 1, year = 2000 still

    }
```

## Пример
Да се напише функция, която превръща низ в число. Поради възможността на низа да не позволява превръщането му в число, да се предостави подходящ начин да се проследи откъде е възникнала грешката. Възможни грешки са:
- Невалиден низ;
- Подаване на nullptr като параметър;
- Overflow на числовия тип;

В случай, че всичко е ок и алгоритъма е изпълнен коректно, да се предостави начин и за уведомяване на това.

```c++
#include <iostream>
#include <climits>

constexpr int64_t INVALID_RESULT = INT64_MIN;

enum class ErrorCode
{
	OK, 
	OVER_FLOW,
	INVALID_STRING,
	NULLPTR
};

struct Result
{
	int64_t result;
	ErrorCode code;
};

bool isDigit(char ch)
{
	return ch >= '0' && ch <= '9';
}

Result createResult(int64_t res, ErrorCode code)
{
	return { res, code };
}

Result from_string_to_digit(const char* str)
{
	if (!str)
	{
		return createResult(INVALID_RESULT, ErrorCode::NULLPTR);
	}

	bool isNegative = (*str == '-');

	if (isNegative)
	{
		++str;
	}

	int64_t res = 0;

	while (*str)
	{
		if (!isDigit(*str))
		{
			return createResult(INVALID_RESULT, ErrorCode::INVALID_STRING);
		}

		if (res * 10 < res)
		{
			return createResult(INVALID_RESULT, ErrorCode::OVER_FLOW);
		}

		res *= 10;
		res += *str - '0';
		++str;
	}

	if (isNegative)
	{
		res *= -1;
	}

	return createResult(res, ErrorCode::OK);
}
int main()
{
	Result res = from_string_to_digit("-12345");

	switch (res.code)
	{
		case ErrorCode::OK: std::cout << res.result << '/n'; break;
		case ErrorCode::OVER_FLOW: std::cout << "Type overflowed!"; break;
		case ErrorCode::INVALID_STRING: std::cout << "Invalid string, conversion not possible!"; break;
		case ErrorCode::NULLPTR: std::cout << "Nullptr given!"; break;
	}
}
```
