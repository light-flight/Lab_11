#define _CRT_SECURE_NO_WARNINGS

/* ЛАБОРАТОРНАЯ РАБОТА 11. УКАЗАТЕЛИ. ДИНАМИЧЕСКИЕ СТРУКТУРЫ ДАННЫХ. ОБРАБОТКА ОДНОСВЯЗНЫХ СПИСКОВ
 *
 * ЗАДАНИЕ
 * Многочлен с целыми коэффициентами можно представить в виде списка.
 * Задать многочлен от Х односвязным списком.
 * Элемент списка содержит показатель степени Х
 * и ненулевой коэффициент при этой степени
 * (в списке не должно быть элементов с одинаковыми степенями).
 * Составить программу, включающую помимо указанных в задании функций,
 * функции создания и вывода списка на экран.
 * Список или списки должны отображаться на экране до обработки и после.
 *
 * 27 вариант
 * Написать функцию, формирующую многочлен(список)
 * из двух многочленов L1, L2 по следующему правилу:
 * в новый многочлен включаются те элементы из L2,
 * степени которых не превосходят минимальную степень из L1.
 *
 * Выполнил Юрьев Георгий, группа ПМ-13
 */

#include <stdio.h>
#include <stdlib.h>

struct polynomial
{
	int coeff;  // коэффициент многочлена
	int degree; // степень многочлена
	struct polynomial *next;
};

typedef struct polynomial* list;

void create(list*);
list find_same_degree(list*, int);
void display(list);
void delete_zero_coeff(list*);
int min_degree(list);
void create_third_polynomial(list*, list*, int);
void merge_sort(list*);
void split(list, list*, list*);
void merge(list*, list, list);

main()
{
	list head1 = NULL, head2 = NULL, head3 = NULL;

	// Вводим первый и второй многочлен.
	puts("Put here the FIRST polynomial.\nEnd by entering a zero coefficient element.");
	create(&head1);
	system("cls");
	puts("Put here the SECOND polynomial\nEnd by entering a zero coefficient element.");
	create(&head2);
	system("cls");

	// Удаляем возможные элементы с нулевым коэффициентом.
	delete_zero_coeff(&head1);
	delete_zero_coeff(&head2);

	// Сортируем элементы списка по степеням членов.
	merge_sort(&head1);
	merge_sort(&head2);

	// Выводим на экран оба получившихся многочлена.
	printf("FIRST polynomial:   ");
	display(head1);
	printf("SECOND polynomial:  ");
	display(head2);

	// Создаем третий многочлен согласно заданию
	create_third_polynomial(&head2, &head3, min_degree(head1));

	// Выводим на экран третий результирующий многочлен.
	printf("THIRD polynomial:   ");
	display(head3);

	system("PAUSE");
}

/* Функция ввода многочлена. Создает список
* с началом по переданному адресу.
*/
void create(list *head)
{
	list current, same_deg, tail = NULL;

	while (1)
	{
		current = (list)malloc(sizeof(struct polynomial));

		// Ввод коэффициента.
		do
		{
			fflush(stdin);
			printf("Put a coefficient: ");
		} while (scanf("%d", &current->coeff) != 1);

		/* Ввод прекращается, когда пользователь вводит элемент
		* с нулевым коэффициентом.
		*/
		if (current->coeff == 0)
		{
			free(current);
			break;
		}

		// Ввод степени.
		do
		{
			fflush(stdin);
			printf("Put a degree: ");
		} while (scanf("%d", &current->degree) != 1);
		printf("\n");

		/* Если пользователь вводит элемент со степенью,
		* которая уже есть в списке, то коэффициенты при этих
		* степенях складываются.
		*/
		if (same_deg = find_same_degree(head, current->degree))
		{
			same_deg->coeff += current->coeff;
			continue;
		}

		// Новый элемент встает в конец списка.
		if ((*head == NULL) && (tail == NULL))
			*head = current;
		else
			tail->next = current;
		tail = current;
		tail->next = NULL;
	}
}

/* Функция находит заданную степень в заданном многочлене.
* Возвращает указатель на элемент списка с искомой степеью.
* Если элементов с этой степенью нет, то возвращает NULL.
*/
list find_same_degree(list *head, int x)
{
	list current;
	for (current = *head; current != NULL; current = current->next)
		if (current->degree == x)
			return current;
	return NULL;
}

/* Функция вывода списка на экран по адресу его первого элемента.
* Сложность вложенных условий обуславливается привычным
* для математиков изображением многочлена, например,
* отсутствие коэффицента/степени, если он/она равен единице,
* отсутствие икса, степень которого ноль и т.д.
*/
void display(list head)
{
	list current;

	if (head == NULL)
	{
		puts("Polinomial doesn't exist!");
	}

	for (current = head; current != NULL; current = current->next)
	{
		// Условия для вывода коэффициента
		if ((current->coeff == 1) && (current == head))
			printf("", current->coeff);
		else
		{
			if ((current->coeff > 1) && (current == head))
				printf("%d", current->coeff);
			else
			{
				if ((current->coeff == 1) && (current != head))
					printf("+", current->coeff);
				else
				{
					if (current->coeff == -1)
						printf("-", current->coeff);
					else
						printf("%+d", current->coeff);
				}
			}

		}
		// Условия для вывода степени
		if (current->degree == 1)
			printf("x");
		else
		{
			if (current->degree < 0)
				printf("x^(%d)", current->degree);
			else
			{
				if (current->degree == 0)
					printf("");
				else
					printf("x^%d", current->degree);
			}
		}
	}
	printf("\n\n");
}

// Функция удаляет все элементы с нулевым коэффициентом
void delete_zero_coeff(list *head)
{
	list current = NULL, zero = NULL;
	while (1)
		/* За один цикл функция удаляет один элемент.
		* Цикл прекращается, если за обход всего списка
		* не нашлось ни одного элемента с нулевым коэффициентом.
		*/
	{
		// Находим элемент с нулевым коэффициентом.
		for (current = *head, zero = NULL; current != NULL; current = current->next)
			if (current->coeff == 0)
				zero = current;

		// Если НЕТ элементов с нулевым коэффициентом, то выйти из функции.
		if (zero == NULL)
			break;

		/* Находим элемент, предшествующий элементу с нулевым коэффициентом.
		* Изменяем укзатели таким образом, чтобы исключить нужный элемент.
		* Если элемент с нулевым коэффициентом стоит в начале списка,
		* то для него выполняются особенные инструкции.
		*/
		for (current = *head; current != NULL; current = current->next)
		{
			// Если первый элемент списка имеет нулевой коэффициент.
			if ((current == *head) && (current == zero))
			{
				*head = (*head)->next;
				free(current);
				break;
			}
			// Если элемент с нулевым коэффициентом не является первым в списке.
			if (current->next == zero)
			{
				current->next = zero->next;
				free(zero);
			}
		}
	}
}

// Функция находит минимальную степень в заданном списке и возвращает её.
int min_degree(list head)
{
	list current = head;
	int degree = current->degree;

	if (head == NULL)
	{
		puts("min_degree: Can't find any elements");
		return;
	}

	for (current = current->next; current != NULL; current = current->next)
	{
		if (current->degree < degree)
			degree = current->degree;
	}

	return degree;
}

/* Функция формирует новый список из элементов второго списка,
* степень которых не превосходит минимальную из первого списка.
* Минимальную степень определяет отдельная функция, которая
* передается в настоящую функцию в качестве третьего аргумента.
*/
void create_third_polynomial(list *head2, list *head3, int min_degree)
{
	list current = NULL, tail = NULL, element;

	for (current = *head2; current != NULL; current = current->next)
		if (current->degree <= min_degree)
		{
			element = (list)malloc(sizeof(struct polynomial));
			element->coeff = current->coeff;
			element->degree = current->degree;
			if ((*head3 == NULL) && (tail == NULL))
				*head3 = element;
			else
				tail->next = element;
			tail = element;
			tail->next = NULL;
		}
}

/* Функция рекурсивно вызывает сама себя,
* передавая части списка. Если в функцию пришёл список
* длинной менее двух элементов, то рекурсия прекращается.
* Далее идёт обратная сборка списка. Сначала из двух списков,
* каждый из которых хранит один элемент, создаётся
* отсортированный список, далее из таких списков собирается
* новый отсортированный список, пока все элементы не будут включены.
*/
void merge_sort(list *head)
{
	list *low = NULL, *high = NULL;

	if ((*head == NULL) || ((*head)->next == NULL))
		return;

	split(*head, &low, &high);
	merge_sort(&low);
	merge_sort(&high);
	merge(head, low, high);
}

// Функция деления списка на 2 части
void split(list head, list *low, list *high)
{
	list fast = NULL, slow = NULL;

	if (head == NULL || head->next == NULL)
	{
		(*low) = head;
		(*high) = NULL;
		return;
	}

	slow = head;
	fast = head->next;

	while (fast != NULL)
	{
		fast = fast->next;
		if (fast != NULL)
		{
			fast = fast->next;
			slow = slow->next;
		}
	}

	(*low) = head;
	(*high) = slow->next;
	slow->next = NULL;
}

// Функция слияния списков.
void merge(list *c, list a, list b)
{
	struct polynomial tmp;
	{

	};

	*c = NULL;
	if (a == NULL)
	{
		*c = b;
		return;
	}
	if (b == NULL)
	{
		*c = a;
		return;
	}

	if (a->degree > b->degree)
	{
		*c = a;
		a = a->next;
	}
	else
	{
		*c = b;
		b = b->next;
	}

	tmp.next = *c;

	while (a && b)
	{
		if (a->degree > b->degree)
		{
			(*c)->next = a;
			a = a->next;
		}
		else
		{
			(*c)->next = b;
			b = b->next;
		}
		(*c) = (*c)->next;
	}
	if (a)
	{
		while (a)
		{
			(*c)->next = a;
			(*c) = (*c)->next;
			a = a->next;
		}
	}
	if (b)
	{
		while (b)
		{
			(*c)->next = b;
			(*c) = (*c)->next;
			b = b->next;
		}
	}

	*c = tmp.next;
}
