mkdir -p build
shopt -s globstar
gcc src/**/*.c -o build/my_game -lraylib -lm -fsanitize=address -g -O0
cp -r src/assets build/
