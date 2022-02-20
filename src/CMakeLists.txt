add_library(${PROJECT_NAME} STATIC
        header.c header.h
        question.c question.h
        message.c message.h
        resource_record.c resource_record.h

        records/a.c records/a.h
        records/aaaa.c records/aaaa.h)
