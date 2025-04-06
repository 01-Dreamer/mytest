all:producer consumer

producer:producer.cpp
	g++ -std=c++17 -w -o $@ $^ -lSimpleAmqpClient -lrabbitmq

consumer:consumer.cpp
	g++ -std=c++17 -w -o $@ $^ -lSimpleAmqpClient -lrabbitmq

clean:
	rm -rf producer
	rm -rf consumer

.PHONY:clean