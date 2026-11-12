package dbms

import (
	"fmt"
	"strconv"
	"strings"
)

type Array struct {
	Items []string
}

func (a *Array) Push(val string, idx int) {
	if idx < 0 || idx >= len(a.Items) {
		a.Items = append(a.Items, val)
	} else {
		a.Items = append(a.Items[:idx], append([]string{val}, a.Items[idx:]...)...)
	}
}

func (a *Array) Del(idx int) bool {
	if idx < 0 || idx >= len(a.Items) {
		return false
	}
	a.Items = append(a.Items[:idx], a.Items[idx+1:]...)
	return true
}

func (a *Array) Get(idx int) string {
	if idx < 0 || idx >= len(a.Items) {
		return "ERROR"
	}
	return a.Items[idx]
}

func (a *Array) Replace(idx int, val string) bool {
	if idx < 0 || idx >= len(a.Items) {
		return false
	}
	a.Items[idx] = val
	return true
}

func (a *Array) Print() {
	fmt.Println(strings.Join(a.Items, " "))
}