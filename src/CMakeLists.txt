add_library(${PROJECT_NAME} STATIC
        header.c header.h
        question.c question.h
        message.c message.h
        resource_record.c resource_record.h

        messages/a.c messages/a.h
        messages/aaaa.c messages/aaaa.h
        main.c)
