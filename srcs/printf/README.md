# ft_printf

## About
`ft_printf` is Hive(42)’s version of `printf`. As the students at Hive must not use any code we didn’t write ourselves (aside from a handful of specified functions), this project was created to give the students access to the most popular output method in C.

## Installation

```makefile
make
```

Include the `libftprintf.a` library and `libftprintf.h` header when compiling your program.

## Usage

Exactly like how you would with printf:

```c
ft_printf("%s is %s's %d\n", "Hive", "Helsinki", 42);
```
![Hiv](https://user-images.githubusercontent.com/78841468/200192741-e433bcaa-5334-4a9a-b660-5e7a846ba695.png)

## Extra features

<details>
  <summary>Print binary number - %b:</summary>

```c
ft_printf("%d is %b in the eyes of the computer\n", 42, 42);
```
![42](https://user-images.githubusercontent.com/78841468/200192758-025eda05-7d11-4cbb-8f6d-e42d2c3d2c50.png)
</details>

<details>
  <summary>Print to file descriptor - $0:</summary>

```c
char *file_name = "file.name";
int fd = open(file_name, O_RDWR);
ft_printf("$0Outputing %x to %s instead of the terminal\n", fd, 42, file_name);
```
![file](https://user-images.githubusercontent.com/78841468/200192772-0e204fa4-6ac4-420f-b44c-86729e811de1.png)
</details>

<details>
  <summary>Print to file - $1:</summary>

```c
ft_printf("$1Who needs a file descriptor anyway (●ˇ∀ˇ●)\n", "file.name");
```
![fil2](https://user-images.githubusercontent.com/78841468/200192781-1e52b96a-3bd3-46ab-b4b1-1a958cf50156.png)
</details>

<details>
  <summary>Color printing $r/$g/$b/$d:</summary>

```c
ft_printf("%$gs printing is %$bs %$rs\n", "Color", "super", "useful");
ft_printf("$gThis will %$rs the default %$bs. Use $$d $dto reset\n", "change", "color");
```
![color](https://user-images.githubusercontent.com/78841468/200192812-f4b08316-3412-41d6-8052-8dc22d9967ef.png)
  
Note: color printing only works on the terminal (not in files)
</details>

## Note
Use “%%” and “$$” to print the character ‘%’ and ‘$’ respectively

```c
ft_printf("%% $$\n");
```
