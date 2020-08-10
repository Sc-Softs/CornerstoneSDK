def get_translate(prompt, default):
    translate = input(f'{prompt}: ')
    return default if translate == '' else translate

def efunc2cpp(func_text):
    func_name = ''
    func_brief = ''
    func_return_type = ''
    func_return_comment = ''
    func_args = []
    type_dict = {
        '字节型': 'uint8_t',
        '短整数型': 'int16_t',
        '整数型': 'int32_t',
        '长整数型': 'int64_t',
        '小数型': 'float',
        '双精度小数型': 'double',
        '逻辑型': 'bool',
        '日期时间型': 'uint64_t',
        '子程序指针': 'uintptr_t',
        '文本型': 'string',
        '字节集': 'const uint8_t*',
    }
    
    for l in func_text.splitlines(False):
        l = l.strip()
        if l.startswith('.子程序 '):
            l = l.replace('.子程序 ', '')
            args = list(map(lambda s: s.strip(), l.split(',')))
            func_name = get_translate(f'function {args[0]}', args[0])
            func_brief = args[0]
            if args[1] in type_dict.keys():
                func_return_type = type_dict[args[1]]
            else:
                func_return_type = args[1]
            func_return_comment = args[3]
        elif l.startswith('.参数 '):
            l = l.replace('.参数 ', '')
            args = list(map(lambda s: s.strip(), l.split(',')))
            name = get_translate(args[0], args[0])
            if args[1] in type_dict.keys():
                type_ = type_dict[args[1]]
            else:
                type_ = args[1]
            comment = args[0]
            if args[3] != '':
                comment += ' ' + args[3]
            special = args[2]
            if special != '':
                special += ' '
            func_args.append((type_, name, comment, special))

    result = f'/**\n * @brief {func_brief}\n'
    for type_, name, comment, special in func_args:
        result += f' * @param {name} {comment}\n'
    if func_return_comment != '':
        result += f' * @return {func_return_comment}\n'
    result += ' */\n'

    result += f'{func_return_type} {func_name}('
    for type_, name, comment, special in func_args:
        result += f'{special}{type_} {name}, '
    if len(func_args) > 0:
        result = result[:-2]
    result += ');\n\n'

    return result

def e2cpp(text):
    func_text = ''
    for l in text.splitlines(False):
        func_text += l + '\n'
        if l == '返回 (ret)':
            yield efunc2cpp(func_text)
            func_text = ''

if __name__ == "__main__":
    with open('e.txt', 'r', encoding='utf8') as f:
        t = f.read()
    gen = e2cpp(t)
    try:
        while True:
            func = next(gen)
            with open('cpp.txt', 'a', encoding='utf8') as f:
                f.write(func)
    except StopIteration:
        pass
