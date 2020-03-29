To build the project I have used the following ‘cmake’ command

cmake . -DGTEST_INCLUDE=../googletest-release-1.8.0/googletest/include/ -DGTEST_LINK=./

The project does have a dependency on GoogleTest you can see I’ve downloaded the latest into a sibling directory
I’ve built ‘libgtest.a’ and included it with the project for convenience 

All the types for my expressions and giving me the framework for the visitors are contained within
AstExpressions.cpp/.h

AstUnitTest.cpp contains all the tests that were built up to drive the development of the code

ExpressionPrinter.cpp/.h has been a valuable debugging/verification tool that has enabled me to put this code together

ExpressionEvaluator.cpp/.h is the main working implementation of the visitor pattern that evaluates the submitted expressions

There are a number of apparent problems that are apparent with this first attempt

1. The biggest problem is ExpressionEvaluator already looks like its doing too much
	Doesn’t sit right having two results for ExpressionEvaluator
	Should ExpressionEvaluator be templatised? integer, boolean, what then with more numeric types? Consideration should be given into how these types would interact.
	Should it instead be split into two different classes?
	The more I add to ExpressionEvaluator (e.g. Equality) the more I’m convinced it should be moved to two separate classes

2. Order of evaluation and operator precedence needs looking at. It doesn’t work at present but does provide a starting point

3. std::make_unique<> syntax is way to verbose needs a better way of composing expressions

4. Have include some implementation in header files. Noticeably BinaryExp and UnaryExp

5. the AstExpression.cpp/.h files contain a number of classes, as the functionality/complexity grew these could be factored out into their own classes
