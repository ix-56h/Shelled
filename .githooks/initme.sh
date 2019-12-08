#!/bin/sh
# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    .githooks                                          :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jerry <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/18 16:22:46 by jerry             #+#    #+#              #
#    Updated: 2019/11/18 16:22:46 by jerry            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

if [ -d ".githooks" ]
then
	for i in $(find .githooks -type f | sed '/\.sh/d')
		do
			i="$(basename $i)"
			ln -sf "$PWD"/.githooks/$i "$PWD"/.git/hooks/$i 2>&-
		done
fi
exit 0
