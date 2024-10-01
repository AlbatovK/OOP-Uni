#ifndef UTILS_HPP

#define UTILS_HPP

/**
 * Reads file contents and returns string without formatting
 * @param path Relative or absolute path to file (ашд
 * @return Contents of a file in raw string format
 * @throws IOException If some I/O problem occurred during file opening or read
 */
std::string readFile(const std::string &path);

/**
 * Writes content to a file. File is automatically created if not exist
 * @param path Relative or absolute path to file
 * @param content Content to write in raw string format
 * @throws If some I/O problem occurred during file opening or write
 */
void writeToFile(const std::string &path, const std::string &content);

#endif
