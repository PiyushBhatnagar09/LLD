#include<bits/stdc++.h>
using namespace std;

class User;
class Vote;
class Question;
class Answer;
class Comment;
class Tag;
class Commentable;
class Votable;

enum class VoteType
{
    UPVOTE=1,
    NEUTRAL=0,
    DOWNVOTE=-1
};

class Vote {
    private:
    shared_ptr<User> voter;
    VoteType type;
    public:
    Vote(shared_ptr<User> user, VoteType type): voter(user), type(type) {}

    shared_ptr<User> getVoter() const {
        return voter;
    }

    VoteType getType() const {
        return type;
    }
};

class Tag {
    string id;
    string name;
    public:
    Tag(string id, string name): id(id), name(name) {}

    string getId() const {
        return id;
    }
    string getName() const {
        return name;
    }
};

class User {
    private:
    string id;
    string name;
    int reputation;

    public:
    User(string id, string name): id(id), name(name)
    {
        reputation=0;
    }

    string getUserId() const {
        return id;
    }

    string getName() const {
        return name;
    }

    int getReputation() const {
        return reputation;
    }

    void updateReputation(int delta) {
        reputation += delta;
        if(reputation<0)
        {
            reputation=0;
        }
    }
};

class Question: public Votable, public Commentable {
    private:
    string id;
    string title;
    string content;
    shared_ptr<User> author;
    time_t creationDate;
    vector<shared_ptr<Answer>> answers;
    vector<shared_ptr<Comment>> comments;
    vector<shared_ptr<Tag>> tags;
    vector<shared_ptr<Vote>> votes;
    shared_ptr<Answer> acceptedAnswer;

    public:
    Question(string id, string title, shared_ptr<User> user): id(id), title(title), author(user)
    {
        acceptedAnswer= nullptr;
        creationDate = time(nullptr);
    }

    void addAnswer(shared_ptr<Answer> answer)
    {
        answers.push_back(answer);
    }

    void acceptAnswer(shared_ptr<Answer> answer)
    {
        acceptedAnswer = answer;
    }

    void vote(shared_ptr<User> voter, VoteType type)
    {
        votes.push_back(make_shared<Vote> (voter, type));
    }

    int getVoteCount() const {
        int count=0;
        for(const auto& vote: votes)
        {
            count += static_cast<int> (vote->getType());
        }
        return count;
    }

    const string& getTitle() const { return title; }
    const string& getContent() const { return content; }
    const string& getId() const { return id; }
};

class Answer : public Votable, public Commentable {
private:
    string id;
    shared_ptr<User> author;
    shared_ptr<Question> question;
    string content;
    bool isAccepted;
    time_t creationDate;
    vector<shared_ptr<Comment>> comments;
    vector<shared_ptr<Vote>> votes;
public:
    Answer(string id, shared_ptr<User> author, shared_ptr<Question> question, const string& content)
        : id(id), author(author), question(question), content(content), isAccepted(false) {
        creationDate = time(nullptr);
    }

    void vote(shared_ptr<User> voter, VoteType type) override {
        votes.push_back(make_shared<Vote>(voter, type));
        author->updateReputation(type == VoteType::UPVOTE ? 10 : -2);
    }

    int getVoteCount() const override {
        int voteCount = 0;
        for (const auto& vote : votes) {
            voteCount += static_cast<int>(vote->getType());
        }
        return voteCount;
    }

    void addComment(shared_ptr<Comment> comment) override {
        comments.push_back(comment);
    }

    const vector<shared_ptr<Comment>>& getComments() const override {
        return comments;
    }

    void markAsAccepted() {
        if (isAccepted) {
            throw runtime_error("This answer is already accepted.");
        }
        isAccepted = true;
        author->updateReputation(15); // Award reputation for accepted answer
    }

    const string& getId() const { return id; }
    const string& getContent() const { return content; }
    bool isAcceptedStatus() const { return isAccepted; }
    const shared_ptr<Question> getQuestion() const { return question; }
};

class Votable {
    public:
    virtual void vote(shared_ptr<User> voter, VoteType type) = 0; //virtual function
    virtual int getVoteCount() const = 0;
    virtual ~Votable() = default;
};

class Commentable {
public:
    virtual void addComment(shared_ptr<Comment> comment) = 0;
    virtual const vector<shared_ptr<Comment>>& getComments() const = 0;
    virtual ~Commentable() = default;
};

class Comment {
    private:
    string id;
    string content;
    shared_ptr<User> author;
    time_t creationDate;
    public:
    Comment(string id, string content, shared_ptr<User> user): id(id), content(content), author(user) {
        creationDate = time(nullptr); //current time
    }

    shared_ptr<User> getAuthor() const {
        return author;
    }
    string getContent() const {
        return content;
    }
};


class StackOverflow {
public:
    static StackOverflow& getInstance() {
        static StackOverflow instance;
        return instance;
    }

    shared_ptr<User> createUser(const string& name, const string& email) {
        auto user = make_shared<User>(name, email);
        users[user->getUserId()] = user;
        return user;
    }

    shared_ptr<Question> postQuestion(shared_ptr<User> author, const string& title, const string& content, const vector<shared_ptr<Tag>>& tags) {
        auto question = make_shared<Question>(author, title, content, tags);
        questions[question->getId()] = question;
        return question;
    }

    shared_ptr<Answer> postAnswer(shared_ptr<User> author, shared_ptr<Question> question, const string& content) {
        auto answer = make_shared<Answer>(author, question, content);
        question->addAnswer(answer);
        answers[answer->getId()] = answer;
        return answer;
    }

    void acceptAnswer(shared_ptr<Answer> answer) {
        auto question = answer->getQuestion();
        question->acceptAnswer(answer);
        answer->markAsAccepted();
    }

    void addComment(shared_ptr<User> author, shared_ptr<Commentable> commentable, const string& content) {
        auto comment = make_shared<Comment>(author, content);
        commentable->addComment(comment);
    }

private:
    StackOverflow() = default;

    unordered_map<string, shared_ptr<User>> users;
    unordered_map<string, shared_ptr<Question>> questions;
    unordered_map<string, shared_ptr<Answer>> answers;
};

int main() {
    // Create users
    auto alice = StackOverflow::getInstance().createUser("Alice", "alice@example.com");
    auto bob = StackOverflow::getInstance().createUser("Bob", "bob@example.com");
    auto charlie = StackOverflow::getInstance().createUser("Charlie", "charlie@example.com");

    // Alice posts a question
    vector<shared_ptr<Tag>> tags = {make_shared<Tag>("java"), make_shared<Tag>("oop")};
    auto javaQuestion = StackOverflow::getInstance().postQuestion(alice, "What is polymorphism in Java?", "Can someone explain polymorphism in Java with an example?", tags);

    // Bob posts an answer
    auto bobAnswer = StackOverflow::getInstance().postAnswer(bob, javaQuestion, "Polymorphism in Java is the ability of an object to take on many forms...");

    // Charlie adds a comment to the question
    StackOverflow::getInstance().addComment(charlie, javaQuestion, "Great question! I'm also interested in learning about this.");

    // Alice adds a comment to Bob's answer
    StackOverflow::getInstance().addComment(alice, bobAnswer, "Thanks for the explanation! Could you provide a code example?");

    // Charlie votes on the question and answer
    javaQuestion->vote(charlie, VoteType::UPVOTE);
    bobAnswer->vote(charlie, VoteType::UPVOTE);

    // Alice accepts Bob's answer
    StackOverflow::getInstance().acceptAnswer(bobAnswer);

    // Print out the current state
    cout << "Question: " << javaQuestion->getTitle() << endl;
    cout << "Asked by: " << javaQuestion->getContent() << endl;
    cout << "Votes: " << javaQuestion->getVoteCount() << endl;

    return 0;
}