mkdir -p build
shopt -s globstar
gcc main.c src/**/*.c -o build/my_game -lraylib -lm -g -O0
cp -r src/assets build/
