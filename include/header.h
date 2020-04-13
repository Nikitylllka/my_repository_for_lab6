#include <iostream>
#include <picosha2.h>
#include <thread>
#include <vector>
#include <mutex>
#include <cstring>
#include <string>
#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/log/support/date_time.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/sinks.hpp>
#include <boost/core/null_deleter.hpp>
#include <boost/log/expressions/keyword.hpp>

using namespace std;

void log_fileANDconsole() {
    // Определение уровня логирования
    boost::log::register_simple_formatter_factory
            <boost::log::trivial::severity_level, char>("Severity");

    //инициализация лога в файла
    boost::log::add_file_log
            (
                    boost::log::keywords::file_name = "/tmp/Log_%N.log",
                    boost::log::keywords::rotation_size = 10 * 1024 * 1024,
                    boost::log::keywords::time_based_rotation = boost::log::sinks::file::
                    rotation_at_time_point{0, 0,0,},
                    boost::log::keywords::format = "[%TimeStamp%] [%ThreadID%] [%Severity%]: %Message%"
            );

    //инициализация лога в консоль
    boost::log::add_console_log
            (
                    std::cout,
                    boost::log::keywords::format =
                            "[%TimeStamp%] [%ThreadID%] [%Severity%]: %Message%");

    boost::log::add_common_attributes();
}


string random_string(const int len) {

    static const char alph[] =
            "abcdefghijklmnopqrstuvwxyz"
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "1234567890";
    string s;
    for (int i = 0; i < len; ++i) {
        char tmp = alph[rand() % (sizeof(alph) - 1)];
        s = s + tmp;
    }
    return s;
}

int random_len() {
    int t;

    t = std::rand() % 10;

    if (t == 0) {
        int f = 0;
        while (f == 0) {
            t = std::rand() % 10;
            if (t > 0) {
                f++;
            }
        }
    }
    return t;
}

void Start() {
    int i = 0;

    while (i == 0) {
        int r = random_len();

        string test = random_string(r);

        string hash = picosha2::hash256_hex_string(test);

        int pos = hash.find("0000");

        if (pos == 60) {
            cout << "~~~~~~~~~~~~SUCCESS and END for ID thread = " << this_thread::get_id() << " \t~~~~~~~~~~~~"
                 << endl;
            cout << " '" << hash << "'" << endl;
            cout << " String : " << test << "" << endl;
            i++;
            BOOST_LOG_TRIVIAL(info) << "SUCCESS SHA256: " << hash;
            return;
        }
        BOOST_LOG_TRIVIAL(trace) << "SHA256: " << hash << " ID thread'a : "
                                 << this_thread::get_id() << " length string = "
                                 << r << " string : " << test;
    }
}
