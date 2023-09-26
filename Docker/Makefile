SRCS	=	./docker-compose.yml

all:
	mkdir -p /home/tnoulens/nm
	docker-compose -f $(SRCS) up --build -d
	docker container exec -it nm fish

start:
	docker-compose -f $(SRCS) start

stop:
	docker-compose -f $(SRCS) stop

down:
	docker-compose -f $(SRCS) down

ps:
	docker-compose -f $(SRCS) ps

fclean:
	docker stop $$(docker ps -qa);\
    docker rm $$(docker ps -qa);\
    docker rmi -f $$(docker images -qa);\
	docker system prune -af

re: fclean
	@$(MAKE) all

prune:
	docker system prune -f

.PHONY:	all up down ps top clean fclean prune
