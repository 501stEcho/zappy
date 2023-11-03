/*
** EPITECH PROJECT, 2023
** B-YEP-400-LYN-4-1-zappy-valentin.nouri
** File description:
** tests_token
*/

#include <criterion/criterion.h>
#include <string.h>

#include "command.h"

Test(token_tests, creation)
{
    char *token_content = strdup("Test");
    node_t *token = create_token(token_content);

    cr_assert_not_null(token);
    free(token_content);
    free(token);
}

Test(token_tests, token_free)
{
    char *token_content = strdup("Test");
    char *older = token_content;
    node_t *token = create_token(token_content);

    free_token(token);
}

Test(token_tests, extraction)
{
    char *input = strdup("This" "  \t " "\"is a Test\"" "\" ");
    char *older = input;
    char *token = NULL;

    token = extract_token(&input);
    cr_assert_str_eq(token, "This");
    free(token);
    token = extract_token(&input);
    cr_assert_str_eq(token, "");
    free(token);
    input += strlen("  \t ");
    token = extract_token(&input);
    cr_assert_str_eq(token, "\"is a Test\"");
    free(token);
    token = extract_token(&input);
    cr_assert_null(token);
    free(older);
}
