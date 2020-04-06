char *alloc_check(char *input, int cpt)
{
  int alloc;
  char *alias;

  alloc = 0;
  while (input[cpt] != ' ' && input[cpt])
  {
    alloc += 1;
    cpt += 1;
  }
  if (!(alias = (char*)malloc(sizeof(char) * (alloc + 1))))
    return (NULL);
  cpt -= alloc;
  alloc = 0;
  while (input[cpt] && input[cpt] != ' ')
  {
    alias[alloc] = input[cpt];
    alloc++;
    cpt += 1;
  }
  alias[alloc] = '\0';
  return (alias);
}

int  ignore_quotes(char *input, int c, int cpt)
{
  cpt++;
  while (input[cpt] != c && input[cpt])
    cpt++;
  cpt++;
  return (cpt);
}

char *next_arg(char *input, int *cpt)
{
  char *to_check;
  int  to_malloc;
  int  blank;
  int  id;

  to_malloc = *cpt;
  id = 0;
  while (input[to_malloc] == ' ' && input[to_malloc])
    to_malloc++;
  cpt = ignore_quotes_n_spaces();
  blank = to_malloc;
  while (input[to_malloc] != ' ' && input[to_malloc])
    to_malloc++;
  if (!(to_check = (char*)malloc(sizeof(char) * (to_malloc - blank + 1))))
    return (0);
  while (blank < to_malloc)
  {
    to_check[id] = input[blank];
    id++;
    blank++;
  }
  to_check[id] = '\0';
  *cpt = to_malloc;
  return (to_check);
}

int  ignore_args_n_op(char *input, int cpt)
{
  char *to_check;

  while ((to_check = next_arg(input, &cpt)))
  {
    ft_printf("to_check : %s\n", to_check);

    free(to_check);
  }
  return (cpt);
}

char      *check_alias(char *input, int *cpt)
{
  char *alias;

  if (!(alias = alloc_check(input, *cpt)))
    return (input);
  input = print_alias(alias, input, *cpt);
  *cpt += ft_strlen(alias);

  while (input[*cpt] == ' ' && input[*cpt])
    *cpt += 1;
  *cpt -= 1;
  free(alias);
  return (input);
}
