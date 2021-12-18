stack = []
for item in input().split():
    if item == '+':
        stack.append(stack.pop() + stack.pop())
    elif item == '-':
        stack.append(-stack.pop() + stack.pop())
    elif item == '*':
        stack.append(stack.pop() * stack.pop())
    else:
        stack.append(int(item))


print(stack[0])
