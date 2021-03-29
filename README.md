# TP BLOCKCHAIN TASK #04 
# Pseudo Random Distribution


### What is it? 👀

This program equally and deterministically distribute ___N___ tickets between ___M___ students.  
PRNG algorithm is based on a [AES](https://en.wikipedia.org/wiki/Advanced_Encryption_Standard).

### USAGE 🌍

1. ⭐ Star this repo.
2. 📂 Clone this repo (e.g. via ```git clone```).
```sh
git clone https://github.com/sokolcom/tp-blockchain-task04.git
```
3. 🔨 Run ```make``` in the repo directory to build the program (```app.out```).
```sh
make
```
4. 🚀 To run program simply execute:
```sh
/app.out --file <filename> --numbilets <n> --parameter <param>
```
where
* `--file` - filename w/ list of names (one name per line);
* `--numbilets` - amount of tickets to distribute;
* `--param` - an integer parameter which determines the distribution.

5. 🔍 You can run ```make test```, which ivokes 
```sh
/app.out --file data/students_30.txt --numbilets 20 --parameter 424124
 ```
 to test program.
