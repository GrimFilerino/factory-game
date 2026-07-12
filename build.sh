mkdir -p build
shopt -s globstar
gcc src/**/*.c -o build/my_game -lraylib -lm
cp -r src/assets build/
