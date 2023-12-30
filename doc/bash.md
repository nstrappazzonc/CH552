
```bash
toBin () {
  printf "%08d\n" $(dc -e "$1 2op")
}

toHex () {
  printf '%x\n' $1
}

$ toBin 10
00001010

$ toHex 10
a
```
