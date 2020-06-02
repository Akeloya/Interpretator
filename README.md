[![License: MIT](https://img.shields.io/github/license/Akeloya/interpretator)](https://github.com/Akeloya/Interpretator/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/v/release/Akeloya/Interpretator.svg)](https://github.com/Akeloya/Interpretator/releases/latest)

# Interpretator
My college project when I was 17 years old (3-rd course HCI NSU). The project implements a C-like language syntax that is interpreted and executed by the application.
Мой семестровый проект в ВКИ НГУ в 17 лет (3 курс). Проект реализует C-подобный синтаксис языка, интерпретируемый и выполняемый в приложении

## Table of contents (Содержание)
- English
  - [Perpose](#Perpose)
  - [Results](#Results)
  - [Code quality](#Code-quality)
  - [Future Project Development](#Future-Project-Development)
  - [Algorythm for search prime numbers](#Algorythm-for-search-prime-numbers)

- Русский
  - [Цель](#Цель)
  - [Результаты](#Результаты)
  - [Качество кода](#Качество-кода)
  - [Будущие изменения](#Будущие-изменения)
  - [Алгоритм поиска проистых чисел](#Algorythm-for-search-prime-numbers)

## Perpose

The project was implemented as a course work for interpreters of programming languages or interpretation of user actions. Students were given the task to independently develop:
- Language (or set of actions) for interpretation (syntax, semantics)
- Data structures and algorithms for language parsing
- Data structures and algorithms for interpreting the language and displaying (output) the results of the application

## Results

As a defense of the course project, the student, together with the teacher, determined test cases sufficient to protect the work on the exam. The main test used to protect the project was selected algorithm for finding prime numbers.

## Code quality

The college subjects did not include code design courses, project management, testing, and other disciplines that study code quality. Therefore, the original version of the interpreter has a terrible code structure, despite the fact that test cases are executed correctly.

## Future Project Development
- Improve code quality.
- Write english and russian description interpreteter development stages

## Цель
Проект был реализован как результат курсовой работы по интерпретаторам языков программирования или интерпретации пользовательских действий. Студентам было выдано задание на разработку:
- Языка (набора действий) для интерпретации (синтаксис, семантика)
- Структур данных и алгоритмов разбора выражений на данном языке
- Структур данных и алгоритмов для интерпретации с выводом результатов работы приложения

## Результаты
В качестве защиты данной курсовой работы совместно с преподавателем был выбран алгоритм поиска простых чисел (решето Эратосфена)

## Качество кода
Задание курсового проекта не включало оценку качества кода с точки зрения имплементации ООП, тестирования (кроме успешного выполнения тестовых алгоритмов на защите). Поэтому оригинальная версия интерпретатора ужасна по структуре кода, отсутствию шаблонов программирования, несмотря на успешное выполнение тестового задания.

## Будущие изменения
  - Улучшить качество кода
  - Сделать проект мультиязычным (английский+русский)


## Algorythm for search prime numbers
```cpp
int main()
{
	int i = 0,j = 0,a = 0;
	i = 3;
	while (i<180)
	{
		j = 2;
		a = 0;
		while (j<i)
		{
			if (i % j==0)
			    a = 1;
			j = j+1;
		}
		if (a==0)
		printf(i," ");
		i = i+1;
	}
	return 0;
}	
    	