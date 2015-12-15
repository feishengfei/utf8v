#include <utf8v.h>
#include <thc.h>

void
    test_valid_first_range(void)
{
    unsigned char valid_byte = 0x00;
    ENSURE(1 == valid_first_range(valid_byte));
}

void
    test_invalid_first_range(void)
{
    unsigned char valid_byte = 0x8F;
    ENSURE(0 == valid_first_range(valid_byte));
}

void
    test_valid_second_range(void)
{
    unsigned char valid_bytes[] = {0xC2, 0x80};
    ENSURE(1 == valid_second_range(valid_bytes[0], valid_bytes[1]));
}

void
    test_invalid_second_range(void)
{
    unsigned char valid_bytes[] = {0xC2, 0x70};
    ENSURE(0 == valid_second_range(valid_bytes[0], valid_bytes[1]));
}

void
    test_valid_third_range_first_subrange(void)
{
    unsigned char valid_bytes[] = {0xE0, 0xA1, 0x80};
    ENSURE(1 == valid_third_range(valid_bytes[0],
                                  valid_bytes[1],
                                  valid_bytes[2]));
}

void
    test_valid_third_range_second_subrange(void)
{
    unsigned char valid_bytes[] = {0xE0, 0xA1, 0x80};
    ENSURE(1 == valid_third_range(valid_bytes[0],
                                  valid_bytes[1],
                                  valid_bytes[2]));
}

void
    test_valid_fourth_range_first_subrange(void)
{

    unsigned char valid_bytes[] = {0xF0, 0x90, 0x80, 0x80};
    ENSURE(1 == valid_fourth_range(valid_bytes[0],
                                   valid_bytes[1],
                                   valid_bytes[2],
                                   valid_bytes[3]));
}

void
    test_valid_fourth_range_second_subrange(void)
{

    unsigned char valid_bytes[] = {0xF2, 0x80, 0x80, 0x80};
    ENSURE(1 == valid_fourth_range(valid_bytes[0],
                                   valid_bytes[1],
                                   valid_bytes[2],
                                   valid_bytes[3]));
}

void
    test_valid_fourth_range_third_subrange(void)
{

    unsigned char valid_bytes[] = {0xF4, 0x80, 0x80, 0x80};
    ENSURE(1 == valid_fourth_range(valid_bytes[0],
                                   valid_bytes[1],
                                   valid_bytes[2],
                                   valid_bytes[3]));
}

void
    test_extract_sequence_length_zero_length(void)
{
    unsigned char valid_byte = 0x00;
    ENSURE(0 == extract_sequence_length(valid_byte));
}

void
    test_extract_sequence_length_one_length(void)
{
    unsigned char valid_byte = 0xC2;
    ENSURE(1 == extract_sequence_length(valid_byte));
}

void
    test_extract_sequence_length_two_length(void)
{
    unsigned char valid_byte = 0xE0;
    ENSURE(2 == extract_sequence_length(valid_byte));
}

void
    test_extract_sequence_length_three_length(void)
{
    unsigned char valid_byte = 0xF4;
    ENSURE(3 == extract_sequence_length(valid_byte));
}

void
    test_validate_just_null(void)
{
    unsigned char just_null[] = {0x00};
    ENSURE(0 == utf8v_validate(just_null, 1));
}

void
    test_validate_highest_byte(void)
{
    unsigned char highest_byte[] = {0xFF};
    ENSURE(1 == utf8v_validate(highest_byte, 1));
}

void
    test_validate_ascii_only(void)
{
    /*                  H     e     l     l     o  */
    unsigned char hello[] = {0x48, 0x65, 0x6C, 0x6C, 0x6F};
    ENSURE(0 == utf8v_validate(hello, 5));
}

void
    test_validate_second_range_sequence(void)
{
    unsigned char bytes_sequence[] = {0xC4, 0xE3};
    ENSURE(1 == utf8v_validate(bytes_sequence, 2));
}

void
    test_validate_second_range_sequence_plus_another_byte(void)
{
    unsigned char bytes_sequence[] = {0xC2, 0xBF, 0x48};
    ENSURE(0 == utf8v_validate(bytes_sequence, 3));
}

void
    test_validate_third_range_sequence(void)
{
    unsigned char bytes_sequence[] = {0xE0, 0xA0, 0xBF};
    ENSURE(0 == utf8v_validate(bytes_sequence, 3));
}

void
    test_validate_third_range_sequence_plus_second_range_sequence(void)
{
    unsigned char bytes_sequence[] = {0xE0, 0xA0, 0xBF, 0xC2, 0xBF, 0x48};
    ENSURE(0 == utf8v_validate(bytes_sequence, 6));
}

void
    test_validate_fourth_range_sequence(void)
{
    unsigned char bytes_sequence[] = {0xF0, 0x90, 0x80, 0x80};
    ENSURE(0 == utf8v_validate(bytes_sequence, 4));
}

void
    test_validate_fourth_range_sequence_plus_third_range_sequence(void)
{
    unsigned char bytes_sequence[] = {0xF0, 0x90, 0x80, 0x80, 0xE0, 0xA0, 0xBF};
    ENSURE(0 == utf8v_validate(bytes_sequence, 4));
}

void
    test_validate_size_zero(void)
{
    unsigned char bytes_sequence[] = {0xF0, 0x90, 0x80};
    ENSURE(-1 == utf8v_validate(bytes_sequence, 0));
}

void
    test_validate_second_range_wrong_size(void)
{
    unsigned char bytes_sequence[] = {0xC2, 0xBF};
    ENSURE(-1 == utf8v_validate(bytes_sequence, 1));

}

void
    test_validate_third_range_sequence_wrong_size(void)
{
    unsigned char bytes_sequence[] = {0xE0, 0xA0, 0xBF};
    ENSURE(-1 == utf8v_validate(bytes_sequence, 2));
}

void
    test_validate_fourth_range_wrong_size(void)
{
    unsigned char bytes_sequence[] = {0xF0, 0x90, 0x80, 0x80};
    ENSURE(-1 == utf8v_validate(bytes_sequence, 3));
}

int
    main(int argc, char **argv)
{
    thc_addtest(test_valid_first_range);
    thc_addtest(test_invalid_first_range);
    thc_addtest(test_valid_second_range);
    thc_addtest(test_invalid_second_range);
    thc_addtest(test_valid_third_range_first_subrange);
    thc_addtest(test_valid_third_range_second_subrange);
    thc_addtest(test_valid_fourth_range_first_subrange);
    thc_addtest(test_valid_fourth_range_second_subrange);
    thc_addtest(test_valid_fourth_range_third_subrange);
    thc_addtest(test_extract_sequence_length_zero_length);
    thc_addtest(test_extract_sequence_length_one_length);
    thc_addtest(test_extract_sequence_length_two_length);
    thc_addtest(test_extract_sequence_length_three_length);
    thc_addtest(test_validate_just_null);
    thc_addtest(test_validate_highest_byte);
    thc_addtest(test_validate_ascii_only);
    thc_addtest(test_validate_second_range_sequence);
    thc_addtest(test_validate_second_range_sequence_plus_another_byte);
    thc_addtest(test_validate_third_range_sequence);
    thc_addtest(test_validate_third_range_sequence_plus_second_range_sequence);
    thc_addtest(test_validate_fourth_range_sequence);
    thc_addtest(test_validate_fourth_range_sequence_plus_third_range_sequence);
    thc_addtest(test_validate_size_zero);
    thc_addtest(test_validate_second_range_wrong_size);
    thc_addtest(test_validate_third_range_sequence_wrong_size);
    thc_addtest(test_validate_fourth_range_wrong_size);
    return thc_run(THC_VERBOSE);
}
