package dbms

import (
	"fmt"
	"strconv"
	"strings"
)

type Stack struct {
	Items []string
}

func (s *Stack) Push(val string) { s.Items = append(s.Items, val) }

func (s *Stack) Pop() string {
	if len(s.Items) == 0 {
		return "EMPTY"
	}
	val := s.Items[len(s.Items)-1]
	s.Items = s.Items[:len(s.Items)-1]
	return val
}

func (s *Stack) Peek() string {
	if len(s.Items) == 0 {
		return "EMPTY"
	}
	return s.Items[len(s.Items)-1]
}

func (s *Stack) Print() { fmt.Println(strings.Join(s.Items, " ")) }