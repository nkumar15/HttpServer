g++ -o http_server main.cpp connection.cpp connection_manager.cpp mime_types.cpp reply.cpp request_handler.cpp  request_parser.cpp server.cpp -I/usr/local/boost_1_42_0 -lboost_system -lboost_thread -lpthread -std=c++11

