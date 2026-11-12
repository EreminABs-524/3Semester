package dbms

import (
	"fmt"
	"strconv"
	"strings"
)

type SNode struct {
	Val  string
	Next *SNode
}

type SinglyList struct {
	Head *SNode
	Tail *SNode
	Size int
}

func (l *SinglyList) Push(val, mode, ref string) {
	node := &SNode{Val: val}
	if mode == "head" || l.Head == nil {
		node.Next = l.Head
		l.Head = node
		if l.Tail == nil {
			l.Tail = node
		}
	} else if mode == "tail" {
		l.Tail.Next = node
		l.Tail = node
	} else if mode == "before" {
		if l.Head.Val == ref {
			node.Next = l.Head
			l.Head = node
			return
		}
		cur := l.Head
		for cur.Next != nil && cur.Next.Val != ref {
			cur = cur.Next
		}
		if cur.Next != nil {
			node.Next = cur.Next
			cur.Next = node
		} else {
			fmt.Println("NOT_FOUND")
			return
		}
	} else if mode == "after" {
		cur := l.Head
		for cur != nil && cur.Val != ref {
			cur = cur.Next
		}
		if cur != nil {
			node.Next = cur.Next
			cur.Next = node
			if l.Tail == cur {
				l.Tail = node
			}
		} else {
			fmt.Println("NOT_FOUND")
			return
		}
	}
	l.Size++
}

func (l *SinglyList) Del(mode, ref string) bool {
	if l.Head == nil {
		return false
	}
	if mode == "head" {
		l.Head = l.Head.Next
		if l.Head == nil {
			l.Tail = nil
		}
		l.Size--
		return true
	} else if mode == "tail" {
		if l.Head == l.Tail {
			l.Head, l.Tail = nil, nil
			l.Size--
			return true
		}
		cur := l.Head
		for cur.Next != l.Tail {
			cur = cur.Next
		}
		l.Tail = cur
		l.Tail.Next = nil
		l.Size--
		return true
	} else if mode == "value" {
		if l.Head.Val == ref {
			return l.Del("head", "")
		}
		cur := l.Head
		for cur.Next != nil && cur.Next.Val != ref {
			cur = cur.Next
		}
		if cur.Next != nil {
			if cur.Next == l.Tail {
				l.Tail = cur
			}
			cur.Next = cur.Next.Next
			l.Size--
			return true
		}
	}
	return false
}

func (l *SinglyList) Get(mode string, idx int) string {
	if l.Head == nil {
		return "EMPTY"
	}
	if mode == "head" {
		return l.Head.Val
	}
	if mode == "tail" {
		return l.Tail.Val
	}
	cur, i := l.Head, 0
	for cur != nil {
		if i == idx {
			return cur.Val
		}
		cur = cur.Next
		i++
	}
	return "ERROR"
}

func (l *SinglyList) Search(val string) int {
	cur, i := l.Head, 0
	for cur != nil {
		if cur.Val == val {
			return i
		}
		cur = cur.Next
		i++
	}
	return -1
}

func (l *SinglyList) Print() {
	cur := l.Head
	var res []string
	for cur != nil {
		res = append(res, cur.Val)
		cur = cur.Next
	}
	fmt.Println(strings.Join(res, " "))
}