/***********************************************************************
 *                            T R O K A M
 *                 Free and Open Source Search Engine
 *
 * Service        http://trokam.com/search
 * About          http://trokam.com/pages/about
 * Development    http://dev.trokam.com/
 * Repository     https://github.com/trokam
 * News           https://twitter.com/trokam
 *
 * Copyright (C) 2015, Nicolas Slusarenko
 *                     nicolas.slusarenko@trokam.com
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 **********************************************************************/

/// C
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

/// C++
#include <fstream>
#include <iomanip>
#include <iostream>
#include <iostream>
#include <sstream>
#include <vector>

/// Boost
#include <boost/algorithm/string.hpp>
#include <boost/date_time/posix_time/posix_time_types.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/tokenizer.hpp>

/// JsonCpp
#include <jsoncpp/json/json.h>
#include <jsoncpp/json/value.h>

/// Postgresql
#include <pqxx/pqxx>

/// Trokam
#include "common.h"
#include "converter.h"
#include "db_handler.h"
#include "random.h"
#include "token.h"
	
/// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
///
/// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#if SERVER_PROCESS
    #include "server_log.h"
#else
    #include "desk_log.h"
#endif

/***********************************************************************
 *
 **********************************************************************/
trokam::db_handler::db_handler(trokam::options &options): opt(options)
{
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    /// Connection parameters to database
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    std::string parameters;
    if(opt.db_host() != "")
    {
        parameters+= "host=" + opt.db_host() + " ";
    }

    if(opt.db_name() != "")
    {
        parameters+= "dbname=" + opt.db_name() + " ";
    }

    if(opt.db_user() != "")
    {
        parameters+= "user=" + opt.db_user() + " ";
    }

    LOG(DEBUG, "Database connection parameters: " << parameters);
    db= new postgresql(parameters);
}

/***********************************************************************
 *
 **********************************************************************/
trokam::db_handler::~db_handler()
{
    delete db;
}

/***********************************************************************
 *
 **********************************************************************/
std::string trokam::db_handler::get_cruncher_index(const std::string &cruncher_id)
{
    std::string sentence, index;
    sentence=  "SELECT index ";
    sentence+= "FROM cruncher ";
    sentence+= "WHERE id='" + cruncher_id + "' ";
    db->exec_sql(sentence, index);
    return index;
}

/***********************************************************************
 *
 **********************************************************************/
bool trokam::db_handler::is_valid_user(const std::string &cruncher_id)
{
    std::string sentence, index;
    sentence=  "SELECT index ";
    sentence+= "FROM cruncher ";
    sentence+= "WHERE id='" + cruncher_id + "' ";
    db->exec_sql(sentence, index);

    if(index != "")
    {
        LOG(TRACE, "cruncher is valid");
        return true;
    }
    LOG(WARNING, "cruncher is not valid");    
    return false;
}

/***********************************************************************
 * This method split the 'text' in individual words and then builds
 * a SQL sentence using those words.
 * CAVEAT: It searches up to three words.
 **********************************************************************/
void trokam::db_handler::search(const std::string &text, boost::scoped_ptr<pqxx::result> &answer)
{
    std::vector<std::string> words;
    trokam::token::separate_words(text, words);

    if(words.size() == 1)
    {
        std::string sentence;
        sentence=  "SELECT ratio, ";
        sentence+= "       CAST(ranking.domain as integer), ";
        sentence+= "       CAST(ranking.title as integer), ";
        sentence+= "       CAST(ranking.path as integer), ";
        sentence+= "       url.index, url.value, content.title, content.body ";
        sentence+= "FROM url, word, ranking, content ";
        sentence+= "WHERE url.index=ranking.url_index ";
        sentence+= "AND word.index=ranking.word_index ";
        sentence+= "AND url.index=content.url_index ";
        sentence+= "AND word.value='" + words[0] + "' ";
        sentence+= "ORDER BY ratio DESC ";
        sentence+= "LIMIT 12 ";
        LOG(TRACE, "sentence: " << sentence);
        db->exec_sql(sentence, answer);
    }
    else if(words.size() == 2)
    {
        std::string sentence;
        sentence=  "SELECT (r1.ratio + r2.ratio) as combined, ";
        sentence+= "       (CAST(r1.domain as integer) + CAST(r2.domain as integer)), ";
        sentence+= "       (CAST(r1.title as integer) + CAST(r2.title as integer)), ";
        sentence+= "       (CAST(r1.path as integer) + CAST(r2.path as integer)), ";
        sentence+= "       url.index, url.value, content.title, content.body ";
        sentence+= "FROM url, content, word as w1, word as w2, ranking as r1, ranking as r2 ";
        sentence+= "WHERE url.index=content.url_index ";
        sentence+= "AND url.index=r1.url_index ";
        sentence+= "AND url.index=r2.url_index ";
        sentence+= "AND w1.index=r1.word_index ";
        sentence+= "AND w2.index=r2.word_index ";
        sentence+= "AND w1.value='" + words[0] + "' ";
        sentence+= "AND w2.value='" + words[1] + "' ";
        sentence+= "ORDER BY combined DESC ";
        sentence+= "LIMIT 12 ";        
        LOG(TRACE, "sentence: " << sentence);
        db->exec_sql(sentence, answer);
    }
    else
    {
        std::string sentence;
        sentence=  "SELECT (r1.ratio + r2.ratio + r3.ratio) as combined, ";
        sentence+= "       (CAST(r1.domain as integer) + CAST(r2.domain as integer) + CAST(r3.domain as integer)), ";
        sentence+= "       (CAST(r1.title as integer) + CAST(r2.title as integer) + CAST(r3.title as integer)), ";
        sentence+= "       (CAST(r1.path as integer) + CAST(r2.path as integer) + CAST(r3.path as integer)), ";
        sentence+= "       url.index, url.value, content.title, content.body ";
        sentence+= "FROM url, content, word as w1, word as w2, word as w3, ranking as r1, ranking as r2, ranking r3 ";
        sentence+= "WHERE url.index=content.url_index ";
        sentence+= "AND url.index=r1.url_index ";
        sentence+= "AND url.index=r2.url_index ";
        sentence+= "AND url.index=r3.url_index ";
        sentence+= "AND w1.index=r1.word_index ";
        sentence+= "AND w2.index=r2.word_index ";
        sentence+= "AND w3.index=r3.word_index ";
        sentence+= "AND w1.value='" + words[0] + "' ";
        sentence+= "AND w2.value='" + words[1] + "' ";
        sentence+= "AND w3.value='" + words[2] + "' ";
        sentence+= "ORDER BY combined DESC ";
        sentence+= "LIMIT 12 ";
        LOG(TRACE, "sentence: " << sentence);
        db->exec_sql(sentence, answer);
    }
}

/***********************************************************************
 *
 **********************************************************************/
void trokam::db_handler::get_task(const std::string &cruncher_index, task &user_task)
{
    user_task.task_id= trokam::random::general();
    user_task.task_type= FULL_REPORT;
    get_url_task(user_task.url, user_task.url_index);
    save_task(cruncher_index, user_task);
    book_url(user_task.url_index);
}

/***********************************************************************
 * This method saves the data of a task pairing a cruncher with an URL.
 * IMPROVEMENT: Include also the instance to which is assigned.
 **********************************************************************/
void trokam::db_handler::save_task(const std::string &cruncher_index, const task &user_task)
{
    std::string sentence;
    sentence=  "INSERT INTO task ";
    sentence+= "VALUES (";
    sentence+= "DEFAULT, ";
    sentence+= "'" + cruncher_index + "', ";
    sentence+= "'" + user_task.task_id + "', ";
    sentence+= "'" + user_task.task_type + "', ";
    sentence+= user_task.url_index + ", ";
    sentence+= "false, ";
    sentence+= "now()";
    sentence+= ")";
    db->exec_sql(sentence);
}

/***********************************************************************
 *
 **********************************************************************/
void trokam::db_handler::set_task_finished(const std::string &task_id)
{
    std::string sentence;
    sentence=  "UPDATE ";
    sentence+= "task ";
    sentence+= "SET ";
    sentence+= "completed=true, ";
    sentence+= "date=now() ";
    sentence+= "WHERE task_id='" + task_id + "' ";
    db->exec_sql(sentence);
}

/***********************************************************************
 *
 **********************************************************************/
bool trokam::db_handler::verify_user(std::string cruncher_id)
{
    return true;
}

/***********************************************************************
 * Inserts into the database the report sent by a cruncher.
 **********************************************************************/
void trokam::db_handler::save_full_page_report(const Json::Value &incoming,
                                                     Json::Value &outgoing)
{
    std::string url_index;
    std::string cruncher_id= incoming[CRUNCHER_ID].asString();
    std::string task_id= incoming[TASK_ID].asString();

    boost::algorithm::trim_if(task_id, boost::algorithm::is_any_of(" \n\r"));
    
    if(is_right_assignement(cruncher_id, task_id, url_index))
    {
        if(incoming[STATUS] == OK)
        {
            inject_content(url_index, incoming[FULL_PAGE_REPORT]);
            inject_relevant_words(url_index, incoming[FULL_PAGE_REPORT]);
            inject_urls(url_index, incoming[FULL_PAGE_REPORT]);
            
            set_task_finished(task_id);
            release_url_booking(url_index, "0");
            outgoing[REPLY]= "thanks for the report";            
        }
        else
        {
            std::string download_status= incoming[FAIL_TYPE].asString();
            release_url_booking(url_index, download_status);
            outgoing[REPLY]= "thanks for trying the URL";
        }
    }
    else
    {
        outgoing[REPLY]= "failure, the user might be not registered in trokam.";
    }
}

/***********************************************************************
 *
 **********************************************************************/
void trokam::db_handler::inject_urls(const std::string &url_index,
                                     const Json::Value &report)
{
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    /// The level of the URL is the level of the parent plus one.
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    std::string url_level= get_url_level(url_index);
    int level= trokam::converter::string_to_int(url_level) + 1;
    url_level= trokam::converter::to_string(level);

/*
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    /// The level of the URL is the level of the parent plus one.
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    std::string url_level;
    if(parent_index == "-1")
    {
        url_level= "0";
    }
    else
    {
        url_level= get_url_level(parent_index);  
        int level= trokam::converter::string_to_int(url_level) + 1;
        url_level= trokam::converter::to_string(level);
    }
*/
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    /// Iterates through all URLs in the report, all them have the
    /// same level (url_level) and same parent (url_index).
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    int count= 0;
    for(Json::ValueIterator itr= report[URLS].begin(); itr != report[URLS].end(); itr++)
    {
        /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        /// 
        /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        std::string url= report[URLS][itr.memberName()].toStyledString();
        boost::algorithm::trim_if(url, boost::algorithm::is_any_of(" \n\r\""));

        /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        /// 
        /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        inject_one_url(url, url_level, url_index);
        count++;
    }
    LOG(TRACE, "injected " << count << " urls");
}

/***********************************************************************
 *
 **********************************************************************/
std::string trokam::db_handler::get_url_level(const std::string &url_index)
{
    std::string sentence, answer;
    sentence=  "SELECT level ";
    sentence+= "FROM url ";
    sentence+= "WHERE index='" + url_index + "'";
    db->exec_sql(sentence, answer);
    
    return answer;
}

/***********************************************************************
 *
 **********************************************************************/
void trokam::db_handler::inject_content(const std::string &url_index,
                                        const Json::Value &report)
{
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    /// 
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    std::string title= report[TITLE].asString();
    boost::algorithm::trim_if(title, boost::algorithm::is_any_of(" \n\r\""));

    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    /// 
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    std::string body= report[BODY].asString();

    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    /// 
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    std::string sentence;
    sentence=  "INSERT INTO content ";
    sentence+= "VALUES (";
    sentence+= "DEFAULT, ";
    sentence+= "'" + url_index + "', ";
    sentence+= "'" + title + "', ";
    sentence+= "'" + body + "')";
    db->exec_sql(sentence);
}

/***********************************************************************
 *
 **********************************************************************/
void trokam::db_handler::release_url_booking(const std::string &url_index,
                                             const std::string &download_status)
{
    std::string sentence;
    sentence=  "UPDATE ";
    sentence+= "url ";
    sentence+= "SET ";
    sentence+= "booked=false, ";
    sentence+= "crunched=true, ";
    sentence+= "date_crunched=now(), ";
    sentence+= "download_status='" + download_status + "' ";
    sentence+= "WHERE index='" + url_index + "' ";
    db->exec_sql(sentence);
}

/***********************************************************************
 *
 **********************************************************************/
void trokam::db_handler::book_url(const std::string &url_index)
{
    std::string sentence;
    sentence=  "UPDATE ";
    sentence+= "url ";
    sentence+= "SET ";
    sentence+= "booked=true ";
    sentence+= "WHERE index='" + url_index + "' ";
    db->exec_sql(sentence);
}

/***********************************************************************
 * Verifies if a cruncher has assigned the task id.
 **********************************************************************/
bool trokam::db_handler::is_right_assignement(const std::string &cruncher_id,
                                              const std::string &task_id,
                                              std::string &url_index)
{
    std::string sentence;
    sentence=  "SELECT url_index ";
    sentence+= "FROM task, cruncher ";
    sentence+= "WHERE task.cruncher_index=cruncher.index ";
    sentence+= "AND cruncher.id='" + cruncher_id + "' ";
    sentence+= "AND task_id='" + task_id + "' ";
    db->exec_sql(sentence, url_index);

    if(url_index != "")
    {
        return true;
    }
    LOG(WARNING, "There is no task assigned for this cruncher.");
    return false;
}

/***********************************************************************
 * Inserts one URL into the database.
 * Several filters are applied and the URL could be rejected.
 **********************************************************************/
std::string trokam::db_handler::inject_one_url(const std::string &url,
                                               const std::string &level,
                                               const std::string &parent_index)
{
    std::string protocol;
    std::string null_answer("-1");
    std::string url_index= "-1";

    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    /// An empty string makes ths method return.
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    if(url == "")
    {
        LOG(WARNING, "URL is empty.");
        return null_answer;
    }

    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    /// If the URL has the char ' it is rejected because
    /// method fetch fails.
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    if(trokam::token::it_has_any_chars_of(url, "'"))
    {
        LOG(WARNING, "URL rejected because it has a unwanted character: " << url);
        return null_answer;
    }

    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    /// It tries to get the protocol (http, https, file, etc.) part
    /// of the URL.
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    if(trokam::token::get_protocol(url, protocol) == 1)
    {
        LOG(ERROR, "Could not get protocol for url: " << url);
        return null_answer;
    }

    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    /// The URL must start with 'http://' or 'https://' otherwise
    ///  it is not stored in the database.
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    if((protocol != "http://") &&
       (protocol != "https://"))
    {
        LOG(WARNING, "Protocol '" << protocol << "' rejected for url: " << url);
        return null_answer;
    }

    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    /// Trying to insert the URL.
    /// Exception will rise if URL already exists.
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    std::string sentence;
    sentence=  "INSERT INTO url ";
    sentence+= "VALUES (";
    sentence+= "DEFAULT, ";            ///  index           |  integer
    sentence+= "'" + url + "', ";      ///  value           |  varchar(1000)
    sentence+= parent_index + ", ";    ///  parent          |  integer
    sentence+= level + ", ";           ///  level           |  integer
    sentence+= "false, ";              ///  booked          |  boolean  
    sentence+= "false, ";              ///  crunched        |  boolean    
    sentence+= "now() ";               ///  date_insertion  |  timestamp without time zone
    sentence+= ") ";
    sentence+= "RETURNING index";
    db->exec_sql(sentence, url_index);

    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    /// If URL already exists the return value is "-1"
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    return url_index;
}

/***********************************************************************
 *
 **********************************************************************/
std::string trokam::db_handler::get_word_index(const std::string &word,
                                               const std::string &lang)
{
    std::string word_index= "-1";
    std::string sentence;
    sentence=  "SELECT word.index ";
    sentence+= "FROM word ";
    sentence+= "WHERE value='" + word + "' ";
    sentence+= "AND word.language='" + lang + "' ";
    db->exec_sql(sentence, word_index);
    
    return word_index;
}

/***********************************************************************
 *  Ocurrence for a new word is '1'
 **********************************************************************/
std::string trokam::db_handler::insert_word(const std::string &word,
                                            const std::string &lang)
{
    std::string word_index;
    std::string sentence;

    sentence=  "INSERT INTO word ";
    sentence+= "VALUES (";
    sentence+= "DEFAULT, ";
    sentence+= "'" + word + "', ";
    sentence+= "'" + lang + "'";
    sentence+= ") ";
    sentence+= "RETURNING index";
    db->exec_sql(sentence, word_index);

    LOG(TRACE, "word_index: " << word_index);

    return word_index;
}

/***********************************************************************
 *
 **********************************************************************/
void trokam::db_handler::inject_words(const Json::Value &report)
{
    std::string lang= report[LANGUAGE].asString();

    int count= 0;
    for(Json::ValueIterator itr= report[WORDS].begin(); itr != report[WORDS].end(); itr++)
    {
        std::string word= itr.memberName();
        std::string occurrences= report[WORDS][itr.memberName()].toStyledString();
        boost::algorithm::trim_if(occurrences, boost::algorithm::is_any_of("\n\r"));

        std::string index= get_word_index(word, lang);
        if (index == "-1")
        {
            index= insert_word(word, lang);
        }
        else
        {
            increment_occurrence(index, occurrences);           
        }
        count++;
    }

    LOG(TRACE, "injected " << count << " words");
}


/***********************************************************************
 *
 **********************************************************************/
void trokam::db_handler::inject_relevant_words(const std::string &url_index,
                                               const Json::Value &report)
{
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    /// 
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    std::string lang= report[LANGUAGE].asString();

    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    /// 
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    std::string title= report[TITLE].asString();
    std::string url= get_url(url_index);

    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    /// 
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    std::string protocol, domain, path;
    trokam::token::split_protocol_domain_path(url, protocol, domain, path);

    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    /// 
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    for(Json::ValueIterator itr= report[RELEVANT].begin(); itr != report[RELEVANT].end(); itr++)
    {
        std::string word= itr.memberName();
        std::string ratio= report[RELEVANT][itr.memberName()].toStyledString();
        boost::algorithm::trim_if(ratio, boost::algorithm::is_any_of("\n\r"));

        std::string word_index= get_word_index(word, lang);
        if (word_index == "-1")
        {
            word_index= insert_word(word, lang);
        }

        /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        /// 
        /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        bool in_domain= false, in_title=false, in_path=false;
        std::size_t pos;

        pos= domain.find(word);
        if(pos != std::string::npos)
        {
            in_domain= true;
        }

        pos= title.find(word);
        if(pos != std::string::npos)
        {
            in_title= true;
        }

        pos= path.find(word);
        if(pos != std::string::npos)
        {
            in_path= true;
        }
        
        insert_rank(url_index, word_index, ratio, in_domain, in_title, in_path);
    }
}

/***********************************************************************
 *
 **********************************************************************/
void trokam::db_handler::insert_rank(const std::string &url_index,
                                     const std::string &word_index,
                                     const std::string &ratio,
                                            const bool &domain,
                                            const bool &title,
                                            const bool &path)
{
    std::string sentence;
    sentence=  "INSERT INTO ranking ";
    sentence+= "VALUES(";
    sentence+= url_index + ", ";
    sentence+= word_index + ", ";
    sentence+= ratio + ", ";
    sentence+= trokam::converter::to_string(domain) + ", ";
    sentence+= trokam::converter::to_string(title) + ", ";
    sentence+= trokam::converter::to_string(path);
    sentence+= ")";
    db->exec_sql(sentence);
}

/***********************************************************************
 *
 **********************************************************************/
std::string trokam::db_handler::increment_occurrence(const std::string &index,
                                                     const std::string &qty)
{
    std::string sentence;
    sentence=  "UPDATE occurrence ";
    sentence+= "SET value= value + " + qty + " ";
    sentence+= "WHERE index_word=" + index + " ";
    db->exec_sql(sentence);

    std::string occ;
    sentence=  "SELECT value ";
    sentence+= "FROM occurrence ";
    sentence+= "WHERE index_word=" + index + " ";
    db->exec_sql(sentence, occ);

    return occ;    
}

/***********************************************************************
 * Picking randomly up an URL with a sentence as this one,
 *
 *   std::string sentence;
 *   sentence=  "SELECT index, value ";
 *   sentence+= "FROM url ";
 *   sentence+= "WHERE crunched=false ";
 *   sentence+= "AND booked=false ";
 *   sentence+= "AND level=0 ";    
 *   sentence+= "ORDER BY RANDOM() ";
 *   sentence+= "LIMIT 1 ";
 *   db->exec_sql(sentence, answer);
 *
 * takes around 10 seconds with a database with more than 10 million
 * URLs, which would be a severe limitation.
 **********************************************************************/
std::string trokam::db_handler::get_url_task(std::string &url, std::string &url_index)
{
    boost::scoped_ptr<pqxx::result> answer;

    std::string sentence;
    sentence=  "SELECT index, value ";
    sentence+= "FROM url ";
    sentence+= "WHERE crunched=false ";
    sentence+= "AND booked=false ";
    sentence+= "AND level=0 ";
    sentence+= "ORDER BY index ";
    sentence+= "LIMIT 1";
    db->exec_sql(sentence, answer);

    pqxx::result::const_iterator col= answer->begin();
    if(col != answer->end())
    {
        url_index= col[0].as(std::string());
        url= col[1].as(std::string());
    }
    else
    {
        LOG(FATAL, "table 'url' is empty");
        exit(1);
    }
    return url;
}

/***********************************************************************
 *
 **********************************************************************/
bool trokam::db_handler::is_db_empty()
{
    START;
    std::string sentence;
    std::string answer;

    sentence=  "SELECT index ";
    sentence+= "FROM url ";
    db->exec_sql(sentence, answer);
    if(answer != EMPTY)
    {
        LOG(ERROR, "table 'url' is not empty");
        RETURN(FAIL);
    }
    LOG(DEBUG, "success: table 'url' is empty");
    RETURN(SUCCESS);
}

/***********************************************************************
 *
 **********************************************************************/
std::string trokam::db_handler::get_url(const std::string &url_index)
{
    std::string sentence, answer;
    sentence=  "SELECT value ";
    sentence+= "FROM url ";
    sentence+= "WHERE url.index=" + url_index;
    db->exec_sql(sentence, answer);

    return answer;
}

/***********************************************************************
 *
 **********************************************************************/
void trokam::db_handler::initialize()
{
    if(is_db_empty())
    {
        if(opt.seeds() != "")
        {
            fill_with_urls_in_file(opt.seeds());
        }
        else
        {
            LOG(FATAL, "there is no seed URL or file with URLs supplied to initalize the database");
        }
    }
    else
    {
        LOG(FATAL, "database is not empty, could not initialize");
    }
}

/***********************************************************************
 *
 **********************************************************************/
void trokam::db_handler::fill_with_urls_in_file(std::string file_name)
{
    START;

    int count= 0, processed= 0;
    boost::posix_time::ptime start(boost::posix_time::microsec_clock::local_time());

    std::ifstream file_source(file_name.c_str());
    for(std::string line; std::getline(file_source, line);)
    {
        /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        /// Trimming of unwanted characters.
        /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        boost::algorithm::trim_if(line, boost::algorithm::is_any_of(" \n\r\""));

        /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        /// Inserting an individual URL.
        /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        if(inject_one_url(line) == "-1")
        {
            LOG(WARNING, "could not insert seed URL '" <<  line << "'");
        }
        else
        {
            /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            /// Count only succesful insertions
            /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            count++;
        }
        processed++;

        /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        /// Every 10000 URLs processed display a dot
        /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        if ((count % 10000) == 0)
        {
            LOG(DEBUG, "URLs inserted: " << count << ", still working ...");
        }
    }
    boost::posix_time::ptime end(boost::posix_time::microsec_clock::local_time());
    boost::posix_time::time_duration duration(end - start);
    float period= duration.total_seconds();

    int processign_speed= int(float(processed)/period);
    int insertion_speed= int(float(count)/period);

    LOG(DEBUG, "Duration: " << period << " seconds");
    LOG(DEBUG, "URL processed " << processed << " at " << processign_speed << " URLs per second");
    LOG(DEBUG, "URL inserted  " << count << " at " << insertion_speed << " URLS per second");
    
    END;
}

/***********************************************************************
 * 
 **********************************************************************/
void trokam::db_handler::get_report_of_url(const std::string &url_index,
                                                 std::string &answer)
{
    std::string title, body, url;
    boost::scoped_ptr<pqxx::result> word_rank, urls;

    url= get_url(url_index);
    get_title(url_index, title);
    get_body(url_index, body);
    get_word_rank(url_index, word_rank);

    boost::replace_all(title, " & ", " and ");
    
    answer+= "---\n";
    answer+= "URL\n";
    answer+= "---\n\n";
    answer+= url + "\n\n";
 
    answer+= "-----\n";
    answer+= "TITLE\n";
    answer+= "-----\n\n";
    answer+= title + "\n\n";

    answer+= "+-----------------------------+\n";    
    answer+= "|   word      |    relevance  |\n";
    answer+= "+-----------------------------+\n";    
    
    for(pqxx::result::const_iterator col= word_rank->begin();
        col != word_rank->end();   
        col++)
    {
        std::string word= col[0].as(std::string());
        word= trokam::token::rightPadding(word, 15);
        
        std::string ratio= col[1].as(std::string());
        ratio= trokam::token::leftPadding(ratio, 8);

        std::string line= word + ratio;
        answer+= line + "\n";
    }
    answer+= "\n";
}

/***********************************************************************
 *
 *
 **********************************************************************/
void trokam::db_handler::get_word_rank(const std::string &url_index,
                                             boost::scoped_ptr<pqxx::result> &answer)
{
    std::string sentence;
    sentence=  "SELECT word.value, ranking.ratio ";
    sentence+= "FROM word, ranking ";
    sentence+= "WHERE word.index=ranking.word_index ";
    sentence+= "AND ranking.url_index=" + url_index + " ";
    sentence+= "ORDER BY ranking.ratio DESC ";
    db->exec_sql(sentence, answer);
}

/***********************************************************************
 *
 *
 **********************************************************************/
void trokam::db_handler::get_urls(const std::string &url_index,
                                        boost::scoped_ptr<pqxx::result> &answer)
{
    std::string sentence;
    sentence=  "SELECT url.value ";
    sentence+= "FROM url ";
    sentence+= "WHERE url.parent=" + url_index;
    db->exec_sql(sentence, answer);
}

/***********************************************************************
 *
 *
 **********************************************************************/
void trokam::db_handler::get_url_index(const std::string &url, 
                                             std::string &url_index)
{
    std::string sentence;
    sentence=  "SELECT index ";
    sentence+= "FROM url ";
    sentence+= "WHERE value='" + url + "' ";
    db->exec_sql(sentence, url_index);
}

/***********************************************************************
 *
 *
 **********************************************************************/
void trokam::db_handler::get_title(const std::string &url_index, 
                                         std::string &title)
{
    std::string sentence;
    sentence=  "SELECT content.title ";
    sentence+= "FROM content ";
    sentence+= "WHERE content.url_index=" + url_index + " ";
    db->exec_sql(sentence, title);
}

/***********************************************************************
 *
 *
 **********************************************************************/
void trokam::db_handler::get_body(const std::string &url_index, 
                                        std::string &body)
{
    std::string sentence;
    sentence=  "SELECT content.body ";
    sentence+= "FROM content ";
    sentence+= "WHERE content.url_index=" + url_index + " ";
    db->exec_sql(sentence, body);
}
