#!/bin/sh

./ft_nm $@ > ft.txt
nm $@ > system.txt
diff ft.txt system.txt
