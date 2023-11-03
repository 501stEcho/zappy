/*
** EPITECH PROJECT, 2023
** B-YEP-400-LYN-4-1-zappy-valentin.nouri
** File description:
** tests_communication
*/

#include <criterion/criterion.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "comminucation.h"

Test(communication_tests, communication_write)
{
    communicator_t communicator = {};

    TAILQ_INIT(&communicator.read);
    TAILQ_INIT(&communicator.write);
    communicator.socket = STDERR_FILENO;
    write_to_peer(&communicator);
    enqueue_message(&communicator, WRITE, "Testing write\n", 14);
    write_to_peer(&communicator);
    write_to_peer(&communicator);
    enqueue_message(&communicator, WRITE, "Testing write\n", 14);
    communicator.socket = -1;
    write_to_peer(&communicator);
}

Test(communication_tests, communication_read)
{
    communicator_t communicator = {};
    char *extract = NULL;
    uint16_t len = 0;

    communicator.socket = open("test.txt",
        O_WRONLY | O_TRUNC | O_CREAT, 0644);
    TAILQ_INIT(&communicator.read);
    TAILQ_INIT(&communicator.write);
    write(communicator.socket, "Testing read\n", 13);
    close(communicator.socket);
    communicator.socket = open("test.txt", O_RDONLY);
    read_from_peer(&communicator);
    extract = extract_buffer(BUFFER(TAILQ_FIRST(&communicator.read)), &len);
    cr_assert_str_eq(extract, "Testing read\n");
    free(extract);
    close(communicator.socket);
}

Test(communication_tests, communication_empy)
{
    communicator_t communicator = {};

    TAILQ_INIT(&communicator.read);
    TAILQ_INIT(&communicator.write);
    cr_assert_eq(is_communication_empty(&communicator, READ), true);
    enqueue_message(&communicator, READ, "Test", 4);
    cr_assert_eq(is_communication_empty(&communicator, READ), false);
    cr_assert_eq(is_communication_empty(&communicator, WRITE), true);
    enqueue_message(&communicator, WRITE, "Test", 4);
    cr_assert_eq(is_communication_empty(&communicator, WRITE), false);
}
