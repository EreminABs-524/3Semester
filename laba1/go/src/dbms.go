package dbms

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
)

type DBMS struct {
	Filename string
	Arrays   map[string]*Array
	FLists   map[string]*SinglyList
	LLists   map[string]*DoublyList
	Stacks   map[string]*Stack
	Queues   map[string]*Queue
}

func NewDBMS(filename string) *DBMS {
	return &DBMS{
		Filename: filename,
		Arrays:   make(map[string]*Array),
		FLists:   make(map[string]*SinglyList),
		LLists:   make(map[string]*DoublyList),
		Stacks:   make(map[string]*Stack),
		Queues:   make(map[string]*Queue),
	}
}

func (d *DBMS) Load() {
	file, err := os.Open(d.Filename)
	if err != nil {
		return
	}
	defer file.Close()

	scanner := bufio.NewScanner(file)
	for scanner.Scan() {
		line := scanner.Text()
		fields := strings.Fields(line)
		if len(fields) < 3 {
			continue
		}
		typ, name := fields[0], fields[1]
		count, _ := strconv.Atoi(fields[2])
		
		if typ == "M" {
			arr := &Array{}
			if len(fields) > 3 {
				arr.Items = append(arr.Items, fields[3:]...)
			}
			d.Arrays[name] = arr
		} else if typ == "F" {
			lst := &SinglyList{}
			for i := 0; i < count && i+3 < len(fields); i++ {
				lst.Push(fields[i+3], "tail", "")
			}
			d.FLists[name] = lst
		} else if typ == "L" {
			lst := &DoublyList{}
			for i := 0; i < count && i+3 < len(fields); i++ {
				lst.Push(fields[i+3], "tail", "")
			}
			d.LLists[name] = lst
		} else if typ == "S" {
			st := &Stack{}
			if len(fields) > 3 {
				st.Items = append(st.Items, fields[3:]...)
			}
			d.Stacks[name] = st
		} else if typ == "Q" {
			q := &Queue{}
			if len(fields) > 3 {
				q.Items = append(q.Items, fields[3:]...)
			}
			d.Queues[name] = q
		}
	}
}

func (d *DBMS) Save() {
	file, err := os.Create(d.Filename)
	if err != nil {
		fmt.Println("Error saving file:", err)
		return
	}
	defer file.Close()

	for name, a := range d.Arrays {
		fmt.Fprintf(file, "M %s %s\n", name, a.Save())
	}
	for name, l := range d.FLists {
		fmt.Fprintf(file, "F %s %s\n", name, l.Save())
	}
	for name, l := range d.LLists {
		fmt.Fprintf(file, "L %s %s\n", name, l.Save())
	}
	for name, s := range d.Stacks {
		fmt.Fprintf(file, "S %s %s\n", name, s.Save())
	}
	for name, q := range d.Queues {
		fmt.Fprintf(file, "Q %s %s\n", name, q.Save())
	}
}

func (d *DBMS) PrintAny(name string) {
	if a, ok := d.Arrays[name]; ok {
		a.Print()
	} else if l, ok := d.FLists[name]; ok {
		l.Print()
	} else if l, ok := d.LLists[name]; ok {
		l.Print(false)
	} else if s, ok := d.Stacks[name]; ok {
		s.Print()
	} else if q, ok := d.Queues[name]; ok {
		q.Print()
	} else {
		fmt.Println("NOT_FOUND")
	}
}

func (d *DBMS) Execute(line string) {
	fields := strings.Fields(line)
	if len(fields) == 0 {
		return
	}
	cmd := fields[0]

	if cmd == "SAVE" {
		d.Save()
		fmt.Println("OK")
		return
	}
	if cmd == "LOAD" {
		d.Load()
		fmt.Println("OK")
		return
	}
	if cmd == "PRINT" && len(fields) >= 2 {
		d.PrintAny(fields[1])
		return
	}

	if len(fields) < 2 {
		return
	}
	name := fields[1]
	op := cmd[1:]

	switch cmd[0] {
	case 'M':
		if op == "PUSH" && len(fields) >= 3 {
			if d.Arrays[name] == nil { d.Arrays[name] = &Array{} }
			idx := -1
			if len(fields) >= 4 { idx, _ = strconv.Atoi(fields[3]) }
			d.Arrays[name].Push(fields[2], idx)
			fmt.Println(fields[2])
		} else if op == "DEL" && len(fields) >= 3 {
			idx, _ := strconv.Atoi(fields[2])
			if d.Arrays[name] != nil && d.Arrays[name].Del(idx) { fmt.Println("OK") } else { fmt.Println("ERROR") }
		} else if op == "GET" && len(fields) >= 3 {
			idx, _ := strconv.Atoi(fields[2])
			if d.Arrays[name] != nil { fmt.Println(d.Arrays[name].Get(idx)) } else { fmt.Println("ERROR") }
		} else if op == "LEN" {
			if d.Arrays[name] != nil { fmt.Println(len(d.Arrays[name].Items)) } else { fmt.Println(0) }
		} else if op == "REPLACE" && len(fields) >= 4 {
			idx, _ := strconv.Atoi(fields[2])
			if d.Arrays[name] != nil && d.Arrays[name].Replace(idx, fields[3]) { fmt.Println("OK") } else { fmt.Println("ERROR") }
		}

	case 'F':
		if d.FLists[name] == nil { d.FLists[name] = &SinglyList{} }
		if op == "PUSH" && len(fields) >= 4 {
			mode := fields[3]
			ref := ""
			if len(fields) >= 5 { ref = fields[4] }
			d.FLists[name].Push(fields[2], mode, ref)
			fmt.Println(fields[2])
		} else if op == "DEL" && len(fields) >= 3 {
			mode := fields[2]
			ref := ""
			if len(fields) >= 4 { ref = fields[3] }
			if d.FLists[name].Del(mode, ref) { fmt.Println("OK") } else { fmt.Println("ERROR") }
		} else if op == "GET" && len(fields) >= 3 {
			if fields[2] == "all" { d.FLists[name].Print() } else {
				idx := 0
				if len(fields) >= 4 { idx, _ = strconv.Atoi(fields[3]) }
				fmt.Println(d.FLists[name].Get(fields[2], idx))
			}
		} else if op == "SEARCH" && len(fields) >= 3 {
			fmt.Println(d.FLists[name].Search(fields[2]))
		}

	case 'L':
		if d.LLists[name] == nil { d.LLists[name] = &DoublyList{} }
		if op == "PUSH" && len(fields) >= 4 {
			mode := fields[3]
			ref := ""
			if len(fields) >= 5 { ref = fields[4] }
			d.LLists[name].Push(fields[2], mode, ref)
			fmt.Println(fields[2])
		} else if op == "DEL" && len(fields) >= 3 {
			mode := fields[2]
			ref := ""
			if len(fields) >= 4 { ref = fields[3] }
			if d.LLists[name].Del(mode, ref) { fmt.Println("OK") } else { fmt.Println("ERROR") }
		} else if op == "GET" && len(fields) >= 3 {
			if fields[2] == "all" { d.LLists[name].Print(false) } else if fields[2] == "reverse" { d.LLists[name].Print(true) } else {
				idx := 0
				if len(fields) >= 4 { idx, _ = strconv.Atoi(fields[3]) }
				fmt.Println(d.LLists[name].Get(fields[2], idx))
			}
		} else if op == "SEARCH" && len(fields) >= 3 {
			fmt.Println(d.LLists[name].Search(fields[2]))
		}

	case 'S':
		if d.Stacks[name] == nil { d.Stacks[name] = &Stack{} }
		if op == "PUSH" && len(fields) >= 3 {
			d.Stacks[name].Push(fields[2])
			fmt.Println(fields[2])
		} else if op == "POP" {
			fmt.Println(d.Stacks[name].Pop())
		} else if op == "GET" {
			fmt.Println(d.Stacks[name].Peek())
		}

	case 'Q':
		if d.Queues[name] == nil { d.Queues[name] = &Queue{} }
		if op == "PUSH" && len(fields) >= 3 {
			d.Queues[name].Push(fields[2])
			fmt.Println(fields[2])
		} else if op == "POP" {
			fmt.Println(d.Queues[name].Pop())
		} else if op == "GET" {
			fmt.Println(d.Queues[name].Peek())
		}
	}
}