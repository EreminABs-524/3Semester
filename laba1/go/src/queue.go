package dbms

import (
	"fmt"
	"strconv"
	"strings"
)

type Queue struct {
	Items []string
}

func (q *Queue) Push(val string) { q.Items = append(q.Items, val) }

func (q *Queue) Pop() string {
	if len(q.Items) == 0 {
		return "EMPTY"
	}
	val := q.Items[0]
	q.Items = q.Items[1:]
	return val
}

func (q *Queue) Peek() string {
	if len(q.Items) == 0 {
		return "EMPTY"
	}
	return q.Items[0]
}

func (q *Queue) Print() { fmt.Println(strings.Join(q.Items, " ")) }
