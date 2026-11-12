package main

import (
	"bufio"
	"flag"
	"fmt"
	"os"
	"strings"
	"laba1go/src"
)

func main() {
	fileFlag := flag.String("file", "file.data", "Файл базы данных")
	queryFlag := flag.String("query", "", "Одиночный запрос")
	flag.Parse()

	database := dbms.NewDBMS(*fileFlag)
	database.Load()

	if *queryFlag != "" {
		database.Execute(*queryFlag)
		database.Save()
	} else {
		scanner := bufio.NewScanner(os.Stdin)
		fmt.Println("Введите команду (или 'exit' для выхода):")
		for scanner.Scan() {
			line := strings.TrimSpace(scanner.Text())
			if line == "exit" {
				break
			}
			if line == "" {
				continue
			}
			database.Execute(line)
			database.Save()
		}
	}
}