rm -rf client
gcc -o client client.c -lpthread
rm -rf server
gcc -o server server.c -lpthread -lm
