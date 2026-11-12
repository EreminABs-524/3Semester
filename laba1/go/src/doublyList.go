package dbms

import (
	"fmt"
	"strconv"
	"strings"
)

type DNode struct {
	Val  string
	Prev *DNode
	Next *DNode
}

type DoublyList struct {
	Head *DNode
	Tail *DNode
	Size int
}

func (l *DoublyList) Push(val, mode, ref string) {
	node := &DNode{Val: val}
	if mode == "head" || l.Head == nil {
		node.Next = l.Head
		if l.Head != nil {
			l.Head.Prev = node
		}
		l.Head = node
		if l.Tail == nil {
			l.Tail = node
		}
	} else if mode == "tail" {
		node.Prev = l.Tail
		l.Tail.Next = node
		l.Tail = node
	} else if mode == "before" {
		if l.Head.Val == ref {
			l.Push(val, "head", "")
			return
		}
		cur := l.Head
		for cur != nil && cur.Val != ref {
			cur = cur.Next
		}
		if cur != nil {
			node.Prev = cur.Prev
			node.Next = cur
			cur.Prev.Next = node
			cur.Prev = node
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
			node.Prev = cur
			if cur.Next != nil {
				cur.Next.Prev = node
			} else {
				l.Tail = node
			}
			cur.Next = node
		} else {
			fmt.Println("NOT_FOUND")
			return
		}
	}
	l.Size++
}

func (l *DoublyList) Del(mode, ref string) bool {
	if l.Head == nil {
		return false
	}
	if mode == "head" {
		l.Head = l.Head.Next
		if l.Head != nil {
			l.Head.Prev = nil
		} else {
			l.Tail = nil
		}
		l.Size--
		return true
	} else if mode == "tail" {
		l.Tail = l.Tail.Prev
		if l.Tail != nil {
			l.Tail.Next = nil
		} else {
			l.Head = nil
		}
		l.Size--
		return true
	} else if mode == "value" {
		cur := l.Head
		for cur != nil && cur.Val != ref {
			cur = cur.Next
		}
		if cur != nil {
			if cur.Prev != nil {
				cur.Prev.Next = cur.Next
			} else {
				l.Head = cur.Next
			}
			if cur.Next != nil {
				cur.Next.Prev = cur.Prev
			} else {
				l.Tail = cur.Prev
			}
			l.Size--
			return true
		}
	}
	return false
}

func (l *DoublyList) Get(mode string, idx int) string {
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

func (l *DoublyList) Search(val string) int {
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

func (l *DoublyList) Print(reverse bool) {
	var res []string
	if reverse {
		cur := l.Tail
		for cur != nil {
			res = append(res, cur.Val)
			cur = cur.Prev
		}
	} else {
		cur := l.Head
		for cur != nil {
			res = append(res, cur.Val)
			cur = cur.Next
		}
	}
	fmt.Println(strings.Join(res, " "))
}
