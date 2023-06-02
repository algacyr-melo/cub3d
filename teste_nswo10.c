

int nsow10(char **world_map, int x)
{
    int i;

	int window_height = 5;
    i = 0;
//    if (world_map[x] == NULL)
//        return (1);
    while (x < window_height)
	{
		while (world_map[x][i])
		{
        	if (world_map[x][i] != '1' && world_map[x][i] != '0' &&
				world_map[x][i] != 'N' && world_map[x][i] != 'O'
				&& world_map[x][i] != 'W' && world_map[x][i]!='S')
            	return (0);
/*        	if (world_map[x][i] == 'N' || world_map[x][i] == 'S' ||
            	    world_map[x][i] == 'O' || world_map[x][i] == 'W')
        	{
            	pos_x = x;
            	pos_y = i;
            	direction = world_map[x][i];
            	sign++;
        	}
        	i++;
    	} */
    	if (sign > 1)
			return (0);
		x++;
	}
	return (1);
}

int main()
{
	char **world_map[5][4];

	world_map[0] = "1111";
	world_map[1] = "1001";
	world_map[2] = "1x01";
	world_map[3] = "1111"
	nsow10(world_map, 0);

}

