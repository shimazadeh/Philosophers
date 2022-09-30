# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aguillar <aguillar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/23 16:58:55 by aguillar          #+#    #+#              #
#    Updated: 2022/08/23 20:53:40 by aguillar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

TARGET   = philo

CC       = cc

CFLAGS   = -Wall -Wextra -Werror

LFLAGS   = -pthread

SRCDIR   = src

OBJDIR   = obj

SOURCES  := $(wildcard $(SRCDIR)/*.c)
INCLUDES := $(wildcard $(SRCDIR)/*.h)
OBJECTS  := $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
rm       = rm -f

$(TARGET): $(OBJECTS)
	@$(CC) $(OBJECTS) $(LFLAGS) -o $@

$(OBJECTS):	$(OBJDIR)/%.o :	$(SRCDIR)/%.c
	@$(CC) $(CFLAGS) -c $< -o $@

all: $(TARGET)

bonus: fclean all

clean:
	@$(rm) $(OBJECTS)

fclean: clean
	@$(rm) $(TARGET)

re: fclean all

.PHONY: all clean fclean re bonus
