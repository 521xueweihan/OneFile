'use strict';

/**
 * TTTTTTTTTTTTTTTTTTTTTTTHHHHHHHHH     HHHHHHHHHEEEEEEEEEEEEEEEEEEEEEE
 * T:::::::::::::::::::::TH:::::::H     H:::::::HE::::::::::::::::::::E
 * T:::::::::::::::::::::TH:::::::H     H:::::::HE::::::::::::::::::::E
 * T:::::TT:::::::TT:::::THH::::::H     H::::::HHEE::::::EEEEEEEEE::::E
 * TTTTTT  T:::::T  TTTTTT  H:::::H     H:::::H    E:::::E       EEEEEE
 *         T:::::T          H:::::H     H:::::H    E:::::E
 *         T:::::T          H::::::HHHHH::::::H    E::::::EEEEEEEEEE
 *         T:::::T          H:::::::::::::::::H    E:::::::::::::::E
 *         T:::::T          H:::::::::::::::::H    E:::::::::::::::E
 *         T:::::T          H::::::HHHHH::::::H    E::::::EEEEEEEEEE
 *         T:::::T          H:::::H     H:::::H    E:::::E
 *         T:::::T          H:::::H     H:::::H    E:::::E       EEEEEE
 *       TT:::::::TT      HH::::::H     H::::::HHEE::::::EEEEEEEE:::::E
 *       T:::::::::T      H:::::::H     H:::::::HE::::::::::::::::::::E
 *       T:::::::::T      H:::::::H     H:::::::HE::::::::::::::::::::E
 *       TTTTTTTTTTT      HHHHHHHHH     HHHHHHHHHEEEEEEEEEEEEEEEEEEEEEE
 *
 *    SSSSSSSSSSSSSSS UUUUUUUU     UUUUUUUUPPPPPPPPPPPPPPPPP   EEEEEEEEEEEEEEEEEEEEEERRRRRRRRRRRRRRRRR
 *  SS:::::::::::::::SU::::::U     U::::::UP::::::::::::::::P  E::::::::::::::::::::ER::::::::::::::::R
 * S:::::SSSSSS::::::SU::::::U     U::::::UP::::::PPPPPP:::::P E::::::::::::::::::::ER::::::RRRRRR:::::R
 * S:::::S     SSSSSSSUU:::::U     U:::::UUPP:::::P     P:::::PEE::::::EEEEEEEEE::::ERR:::::R     R:::::R
 * S:::::S             U:::::U     U:::::U   P::::P     P:::::P  E:::::E       EEEEEE  R::::R     R:::::R
 * S:::::S             U:::::U     U:::::U   P::::P     P:::::P  E:::::E               R::::R     R:::::R
 *  S::::SSSS          U:::::U     U:::::U   P::::PPPPPP:::::P   E::::::EEEEEEEEEE     R::::RRRRRR:::::R
 *   SS::::::SSSSS     U:::::U     U:::::U   P:::::::::::::PP    E:::::::::::::::E     R:::::::::::::RR
 *     SSS::::::::SS   U:::::U     U:::::U   P::::PPPPPPPPP      E:::::::::::::::E     R::::RRRRRR:::::R
 *        SSSSSS::::S  U:::::U     U:::::U   P::::P              E::::::EEEEEEEEEE     R::::R     R:::::R
 *             S:::::S U:::::U     U:::::U   P::::P              E:::::E               R::::R     R:::::R
 *             S:::::S U::::::U   U::::::U   P::::P              E:::::E       EEEEEE  R::::R     R:::::R
 * SSSSSSS     S:::::S U:::::::UUU:::::::U PP::::::PP          EE::::::EEEEEEEE:::::ERR:::::R     R:::::R
 * S::::::SSSSSS:::::S  UU:::::::::::::UU  P::::::::P          E::::::::::::::::::::ER::::::R     R:::::R
 * S:::::::::::::::SS     UU:::::::::UU    P::::::::P          E::::::::::::::::::::ER::::::R     R:::::R
 *  SSSSSSSSSSSSSSS         UUUUUUUUU      PPPPPPPPPP          EEEEEEEEEEEEEEEEEEEEEERRRRRRRR     RRRRRRR
 *
 * TTTTTTTTTTTTTTTTTTTTTTTIIIIIIIIIINNNNNNNN        NNNNNNNNYYYYYYY       YYYYYYY
 * T:::::::::::::::::::::TI::::::::IN:::::::N       N::::::NY:::::Y       Y:::::Y
 * T:::::::::::::::::::::TI::::::::IN::::::::N      N::::::NY:::::Y       Y:::::Y
 * T:::::TT:::::::TT:::::TII::::::IIN:::::::::N     N::::::NY::::::Y     Y::::::Y
 * TTTTTT  T:::::T  TTTTTT  I::::I  N::::::::::N    N::::::NYYY:::::Y   Y:::::YYY
 *         T:::::T          I::::I  N:::::::::::N   N::::::N   Y:::::Y Y:::::Y
 *         T:::::T          I::::I  N:::::::N::::N  N::::::N    Y:::::Y:::::Y
 *         T:::::T          I::::I  N::::::N N::::N N::::::N     Y:::::::::Y
 *         T:::::T          I::::I  N::::::N  N::::N:::::::N      Y:::::::Y
 *         T:::::T          I::::I  N::::::N   N:::::::::::N       Y:::::Y
 *         T:::::T          I::::I  N::::::N    N::::::::::N       Y:::::Y
 *         T:::::T          I::::I  N::::::N     N:::::::::N       Y:::::Y
 *       TT:::::::TT      II::::::IIN::::::N      N::::::::N       Y:::::Y
 *       T:::::::::T      I::::::::IN::::::N       N:::::::N    YYYY:::::YYYY
 *       T:::::::::T      I::::::::IN::::::N        N::::::N    Y:::::::::::Y
 *       TTTTTTTTTTT      IIIIIIIIIINNNNNNNN         NNNNNNN    YYYYYYYYYYYYY
 *
 *         CCCCCCCCCCCCC     OOOOOOOOO     MMMMMMMM               MMMMMMMMPPPPPPPPPPPPPPPPP   IIIIIIIIIILLLLLLLLLLL             EEEEEEEEEEEEEEEEEEEEEERRRRRRRRRRRRRRRRR
 *      CCC::::::::::::C   OO:::::::::OO   M:::::::M             M:::::::MP::::::::::::::::P  I::::::::IL:::::::::L             E::::::::::::::::::::ER::::::::::::::::R
 *    CC:::::::::::::::C OO:::::::::::::OO M::::::::M           M::::::::MP::::::PPPPPP:::::P I::::::::IL:::::::::L             E::::::::::::::::::::ER::::::RRRRRR:::::R
 *   C:::::CCCCCCCC::::CO:::::::OOO:::::::OM:::::::::M         M:::::::::MPP:::::P     P:::::PII::::::IILL:::::::LL             EE::::::EEEEEEEEE::::ERR:::::R     R:::::R
 *  C:::::C       CCCCCCO::::::O   O::::::OM::::::::::M       M::::::::::M  P::::P     P:::::P  I::::I    L:::::L                 E:::::E       EEEEEE  R::::R     R:::::R
 * C:::::C              O:::::O     O:::::OM:::::::::::M     M:::::::::::M  P::::P     P:::::P  I::::I    L:::::L                 E:::::E               R::::R     R:::::R
 * C:::::C              O:::::O     O:::::OM:::::::M::::M   M::::M:::::::M  P::::PPPPPP:::::P   I::::I    L:::::L                 E::::::EEEEEEEEEE     R::::RRRRRR:::::R
 * C:::::C              O:::::O     O:::::OM::::::M M::::M M::::M M::::::M  P:::::::::::::PP    I::::I    L:::::L                 E:::::::::::::::E     R:::::::::::::RR
 * C:::::C              O:::::O     O:::::OM::::::M  M::::M::::M  M::::::M  P::::PPPPPPPPP      I::::I    L:::::L                 E:::::::::::::::E     R::::RRRRRR:::::R
 * C:::::C              O:::::O     O:::::OM::::::M   M:::::::M   M::::::M  P::::P              I::::I    L:::::L                 E::::::EEEEEEEEEE     R::::R     R:::::R
 * C:::::C              O:::::O     O:::::OM::::::M    M:::::M    M::::::M  P::::P              I::::I    L:::::L                 E:::::E               R::::R     R:::::R
 *  C:::::C       CCCCCCO::::::O   O::::::OM::::::M     MMMMM     M::::::M  P::::P              I::::I    L:::::L         LLLLLL  E:::::E       EEEEEE  R::::R     R:::::R
 *   C:::::CCCCCCCC::::CO:::::::OOO:::::::OM::::::M               M::::::MPP::::::PP          II::::::IILL:::::::LLLLLLLLL:::::LEE::::::EEEEEEEE:::::ERR:::::R     R:::::R
 *    CC:::::::::::::::C OO:::::::::::::OO M::::::M               M::::::MP::::::::P          I::::::::IL::::::::::::::::::::::LE::::::::::::::::::::ER::::::R     R:::::R
 *      CCC::::::::::::C   OO:::::::::OO   M::::::M               M::::::MP::::::::P          I::::::::IL::::::::::::::::::::::LE::::::::::::::::::::ER::::::R     R:::::R
 *         CCCCCCCCCCCCC     OOOOOOOOO     MMMMMMMM               MMMMMMMMPPPPPPPPPP          IIIIIIIIIILLLLLLLLLLLLLLLLLLLLLLLLEEEEEEEEEEEEEEEEEEEEEERRRRRRRR     RRRRRRR
 *
 * =======================================================================================================================================================================
 * =======================================================================================================================================================================
 * =======================================================================================================================================================================
 * =======================================================================================================================================================================
 */

/**
 * 今天我们要一起写一个编译器。 可能和之前的编译器不太一样，因为这个编译器实在是太 mini 了！迷你到除去注释以外，整个文件大约只有 200 行实际代码。
 * 首先我们将把一些类似 lisp 的函数调用编译成类似 C 的函数调用。如果您不熟悉其中之一，那就先来一个简单快速的介绍：
 * 如果我们有两个函数 `add` 和 `subtract` 他们会写成这样：
 *
 *                  LISP                      C
 *
 *   2 + 2          (add 2 2)                 add(2, 2)
 *   4 - 2          (subtract 4 2)            subtract(4, 2)
 *   2 + (4 - 2)    (add 2 (subtract 4 2))    add(2, subtract(4, 2))
 *
 * 这个对比容易理解吧？这正是我们要编译的。 虽然这不是完整的 LISP 或 C 语法，但它足以展示现代编译器的许多主要部分。
 */

/**
 * 大多数编译器分为三个主要阶段：解析、转换和代码生成：
 *
 * 1. 解析：将原始代码转化为更抽象的代码表示
 *
 * 2. 转换：采用抽象表示并进行操作来执行编译器希望它执行的任何操作
 *
 * 3. 代码生成：把经过转换表示的代码转换为新代码

/**
 * 解析
 * -------
 *
 * 解析通常分为两个阶段：词法分析和句法分析
 *
 * 1. 词法分析：获取原始代码并通过一种称为标记器（或词法分析器 Tokenizer）的东西将其拆分为一种称为标记（Token）的东西。
 *    标记是一个数组，它描述了一个独立的语法片段。这些片段可以是数字、标签、标点符号、运算符等等。
 *
 * 2. 语法分析：获取之前生成的标记（Token），并把它们转换成一种抽象的表示，这种抽象的表示描述了代码语句中的每一个片段以及它们之间的关系。
 *    这被称为中间表示（intermediate representation）或抽象语法树（Abstract Syntax Tree， 缩写为AST）。
 *    AST是一个深度嵌套的对象，用一种更容易处理的方式代表了代码本身，也能给我们更多信息。
 *
 * 对于下面这个句法:
 *
 *   (add 2 (subtract 4 2))
 *
 * 标记可能看起来像这样:
 *
 *   [
 *     { type: 'paren',  value: '('        },
 *     { type: 'name',   value: 'add'      },
 *     { type: 'number', value: '2'        },
 *     { type: 'paren',  value: '('        },
 *     { type: 'name',   value: 'subtract' },
 *     { type: 'number', value: '4'        },
 *     { type: 'number', value: '2'        },
 *     { type: 'paren',  value: ')'        },
 *     { type: 'paren',  value: ')'        },
 *   ]
 *
 * 然后一个抽象语法树（AST）可能看起来像这样：
 *
 *   {
 *     type: 'Program',
 *     body: [{
 *       type: 'CallExpression',
 *       name: 'add',
 *       params: [{
 *         type: 'NumberLiteral',
 *         value: '2',
 *       }, {
 *         type: 'CallExpression',
 *         name: 'subtract',
 *         params: [{
 *           type: 'NumberLiteral',
 *           value: '4',
 *         }, {
 *           type: 'NumberLiteral',
 *           value: '2',
 *         }]
 *       }]
 *     }]
 *   }
 */

/**
 * 转换
 * --------------
 *
 * 编译器的下一个阶段是转换。同样的，获取了 AST 之后再对其进行更改。
 * 它可以用相同的语言操作 AST，也可以将其翻译成一种全新的语言。
 *
 * 让我们来看看如何转换 AST。
 *
 * 你可能会注意到我们的 AST 中的元素看起来非常相似。
 * 这些对象都有具有类型属性。这些中的每一个都称为 AST 的节点。
 * 这些节点在树上定义了属性并描述了树上的每一个独立的部分。
 *
 * 我们可以有一个“NumberLiteral”的节点：
 *
 *   {
 *     type: 'NumberLiteral',
 *     value: '2',
 *   }
 *
 * 或者可能是“CallExpression”的一个节点：
 *
 *   {
 *     type: 'CallExpression',
 *     name: 'subtract',
 *     params: [...嵌套节点放在这里...],
 *   }
 *
 * 在转换 AST 的时候，我们可以通过新增、删除、替换属性来操作节点，我们可以新增节点、删除节点，
 * 或者我们可以在原有的 AST 结构保持不变的状态下创建一个基于它的新的 AST。
 *
 * 由于我们的目标是一种新的语言，所以我们将要专注于创造一个完全新的 AST 来配合这个特定的语言。
 *
 * 遍历
 * ---------
 *
 * 为了浏览所有的这些节点，我们需要遍历它们。
 * 这个遍历过程首先是深度遍历。
 *
 *   {
 *     type: 'Program',
 *     body: [{
 *       type: 'CallExpression',
 *       name: 'add',
 *       params: [{
 *         type: 'NumberLiteral',
 *         value: '2'
 *       }, {
 *         type: 'CallExpression',
 *         name: 'subtract',
 *         params: [{
 *           type: 'NumberLiteral',
 *           value: '4'
 *         }, {
 *           type: 'NumberLiteral',
 *           value: '2'
 *         }]
 *       }]
 *     }]
 *   }
 *
 * 对于上面那个 AST，我们会：
 *
 *   1.Program-首先从 AST 的顶层开始
 *   2. CallExpression（add）-移动到程序主体的第一个元素
 *   3. NumberLiteral（2）-移动到 NumberLiteral 参数的第一个元素
 *   4. CallExpression (subtract) - 移动到 CallExpression 参数的第二个元素
 *   5. NumberLiteral (4) - 移动到 CallExpression 参数的第一个元素
 *   6. NumberLiteral (2) - 移动到 CallExpression 参数的第二个元素
 *
 * 如果我们直接操作这个 AST，而不是创造一个单独的 AST，我们很有可能会在这里引入各种抽象。
 * 但是仅仅访问树中的每个节点对于我们来说想做和能做的事情已经很多了。
 *
 * 使用访问（visiting）这个词是因为这是一种模式，代表在对象结构内对元素进行操作。
 *
 * 访问者（Visitors）
 * --------
 *
 * 这里的基本思想是我们将创建一个“访问者”对象，该对象具有接受不同节点类型的方法。
 *
 *   var visitor = {
 *     NumberLiteral() {},
 *     CallExpression() {},
 *   };
 *
 * 当我们遍历我们的 AST 时，只要我们“进入”一个匹配类型的节点，我们就会调用这个“访问者”的方法。
 * 为了使他能够有效，我们还将传递这个节点和它对父节点的引用。
 *
 *   var visitor = {
 *     NumberLiteral(node, parent) {},
 *     CallExpression(node, parent) {},
 *   };
 *
 * 但是，也存在在“退出”时调用事物的可能性。想象一下我们之前列表形式的树结构：
 *
 *   - Program
 *     - CallExpression
 *       - NumberLiteral
 *       - CallExpression
 *         - NumberLiteral
 *         - NumberLiteral
 *
 * 当我们向下遍历时，我们将到达有死胡同的分支。当我们完成树的每个分支时就“退出”它。
 * 
 * 所以顺着树往下走时，我们可以“进入”每个节点，而当往上走时就“退出”。
 *
 *   -> Program (enter)
 *     -> CallExpression (enter)
 *       -> Number Literal (enter)
 *       <- Number Literal (exit)
 *       -> Call Expression (enter)
 *          -> Number Literal (enter)
 *          <- Number Literal (exit)
 *          -> Number Literal (enter)
 *          <- Number Literal (exit)
 *       <- CallExpression (exit)
 *     <- CallExpression (exit)
 *   <- Program (exit)
 *
 * 为了支持这点，我们的“访问者”的最终形式应该是这样：
 *
 *   var visitor = {
 *     NumberLiteral: {
 *       enter(node, parent) {},
 *       exit(node, parent) {},
 *     }
 *   };
 */

/**
 * 代码生成
 * ---------------
 *
 * 编译器的最后一步是代码生成。有时候编译器会做一些和转换重叠的事情，但是大部分情况下，
 * 代码生成只是意味着将我们的 AST 取出并进行字符串化。
 *
 * 代码生成器有几种不同的工作方式，一些编译器直接将之前的标记重复使用，
 * 另一些会创建代码的单独表示，这样他们就可以线性的打印节点，
 * 但是据我所知大部分编译器将会使用我们刚刚创建的相同的 AST，这是我们需要重点关注的。
 *
 * 实际上，我们的代码生成器知道如何“打印” AST 的所有不同节点类型，
 * 并且它将递归调用自身来打印嵌套节点，直到所有内容都打印成一长串代码。
 */

/**
 * 就是这样！这就是编译器中所有不同的部分。
 * 现在这并不是说每个编译器看起来都和我在这里描述的完全一样。
 * 编译器有许多不同的用途，它们可能比我说的这些步骤更加的详细。
 *
 * 但是现在你应该对大多数编译器有了一个大致的了解。
 * 现在我已经解释了所有这些，你们都可以编写自己的编译器了，对吧？
 * 
 * 好了开个玩笑，让我来帮助你从这里慢慢编写一个简单的编译器吧！
 */

/**
 * ============================================================================
 *                                   (/^▽^)/
 *                                THE TOKENIZER!
 * ============================================================================
 */

/**
 * 我们将从解析的第一阶段开始：词法分析和标记器。
 * 我们只要将我们的代码字符串分解成一个标记数组：
 *
 *   (add 2 (subtract 4 2))   =>   [{ type: 'paren', value: '(' }, ...]
 */

// 我们从接收一个代码输入字符串（input）开始，并且我们还要做两件事...
function tokenizer(input) {
  
  // `current` 变量就像一个指光标一样让我们可以在代码中追踪我们的位置
  let current = 0;
  
  // `tokens` 数组用来存我们的标记
  let tokens = [];
  
  // 首先创建一个`while`循环，在循环里面我们可以将`current`变量增加为我们想要的值
  // 做这一步的原因是因为我们想要在一个循环里多次增加`current`变量的值，因为我们的标记的长度不确定
  while (current < input.length) {
    
    // 我们还将在 `input` 中存储 `current` 字符
    let char = input[current];
    
    // 我们要检查的第一件事是一个左括号。 这稍后将用于 `CallExpression` 但现在我们只关心字符。
    // 检查是否有一个左括号:
    if (char === '(') {
      
      // 如果有，我们会存一个类型为 `paren` 的新标记到数组，并将值设置为一个左括号。
      tokens.push({
        type: 'paren',
        value: '(',
      });
      
      // `current`自增
      current++;
      
      // 然后继续进入下一次循环。
      continue;
    }
    
    // 接下去检查右括号， 像上面一样
    if (char === ')') {
      tokens.push({
        type: 'paren',
        value: ')',
      });
      current++;
      continue;
    }
    
    // 接下去我们检查空格，这对于我们来说就是为了知道字符的分割，但是并不需要存储为标记。
    
    // 所以我们来检查是否有空格的存在，如果存在，就继续下一次循环，做除了存储到标记数组之外的其他操作即可
    let WHITESPACE = /\s/;
    if (WHITESPACE.test(char)) {
      current++;
      continue;
    }
    
    // **首先我们从表达式的值中来入手，这里简单举例子就只检查了两种类型的值
    // **一种是数字类型，一种是字符串类型
    
    // 接下去的标记类型是数字. 这和我们之前看到的不太一样
    // 因为数字可以是任何数量的字符，我们希望将整个字符序列捕获称为一个标记
    //
    //   (add 123 456)
    //        ^^^ ^^^
    //        只有两个单独的标记
    //
    // 因此，当我们遇到序列中的第一个数字时，我们就开始了
    let NUMBERS = /[0-9]/;
    if (NUMBERS.test(char)) {
      
      // 我们将创建一个`value`字符串，并把字符推送给他
      let value = '';
      
      // 然后我们将遍历序列中的每个字符，直到遇到一个不是数字的字符
      // 将每个作为数字的字符推到我们的 `value` 并随着我们去增加 `current`
      // 这样我们就能拿到一个完整的数字字符串，例如上面的 123 和 456，而不是单独的 1 2 3 4 5 6
      while (NUMBERS.test(char)) {
        value += char;
        char = input[++current];
      }
      
      // 接着我们把数字放到标记数组中，用数字类型来描述区分它
      tokens.push({ type: 'number', value });
      
      // 继续外层的下一次循环
      continue;
    }
    
    // 我们还将在我们的语言中添加对字符串的支持，可以是任何
    // 用双引号 (") 括起来的文本。
    //
    //   (concat "foo" "bar")
    //            ^^^   ^^^ 字符串标记
    //
    // 从检查开头的双引号开始:
    if (char === '"') {
      // 保留一个 `value` 变量来构建我们的字符串标记。
      let value = '';
      
      // 我们将跳过编辑中开头的双引号
      char = input[++current];
      
      // 然后我们将遍历每个字符，直到我们到达另一个双引号
      while (char !== '"') {
        value += char;
        char = input[++current];
      }
      
      // 跳过相对应闭合的双引号.
      char = input[++current];
      
      // 把我们的字符串标记添加到标记数组中
      tokens.push({ type: 'string', value });
      
      continue;
    }
    
    // 最后一种标记的类型是名称。这是一个字母序列而不是数字，这是我们 lisp 语法中的函数名称
    //
    //   (add 2 4)
    //    ^^^
    //    名称标记
    //
    let LETTERS = /[a-z]/i;
    if (LETTERS.test(char)) {
      let value = '';
      
      // 同样，我们遍历所有，并将它们完整的存到`value`变量中
      while (LETTERS.test(char)) {
        value += char;
        char = input[++current];
      }
      
      // 并把这种名称类型的标记存到标记数组中，继续循环
      tokens.push({ type: 'name', value });
      
      continue;
    }
    
    // 如果到最后我们还没有匹配到一个字符，那就抛出一个异常错误并完全退出
    throw new TypeError('I dont know what this character is: ' + char);
  }
  
  // 在标记器执行结束后，直接返回标记数组即可
  return tokens;
}

/**
 * ============================================================================
 *                                 ヽ/❀o ل͜ o\ﾉ
 *                                THE PARSER!!!
 * ============================================================================
 */

/**
 * 对于解析器来说，我们要把我们的标记数组变成一个 AST：
 *
 *   [{ type: 'paren', value: '(' }, ...]   =>   { type: 'Program', body: [...] }
 */

//  因此我们先定义一个`parser`函数用来接收我们的`tokens`数组
function parser(tokens) {

  // 同样的我们保持一个`current`变量当作光标来供我们使用
  let current = 0;

  // 但是这一次，我们我们将使用递归来替代之前使用的 whie 循环
  // 先定义一个`walk`函数
  function walk() {

    // 在 walk 函数里面，我们首先获取`current`标记
    let token = tokens[current];

    // 我们将把每种类型的标记分成不同的代码路径
    // 先从`number`类型的标记开始.

    // 首先先检查一下是否有`number`标签.
    if (token.type === 'number') {

      // 如果找到一个,就增加`current`.
      current++;

      // 然后我们就能返回一个新的叫做`NumberLiteral`的 AST 节点，并赋值
      return {
        type: 'NumberLiteral',
        value: token.value,
      };
    }

    // 对于字符串来说，也是和上面数字一样的操作。新增一个`StringLiteral`节点
    if (token.type === 'string') {
      current++;

      return {
        type: 'StringLiteral',
        value: token.value,
      };
    }

    // 接下去我们要寻找调用的表达式（CallExpressions）
    // 从找到第一个左括号开始
    if (
      token.type === 'paren' &&
      token.value === '('
    ) {

      // 我们将增加`current`来跳过这个插入语，因为在 AST 树中我们并不关心这个括号
      token = tokens[++current];

      // 我们创建一个类型为“CallExpression”的基本节点，并把当前标记的值设置到 name 字段上
      // 因为左括号的下一个标记就是这个函数的名字
      let node = {
        type: 'CallExpression',
        name: token.value,
        params: [],
      };

      // 继续增加`current`来跳过这个名称标记
      token = tokens[++current];

      // 现在我们要遍历每一个标记，找出其中是`CallExpression`的`params`，直到遇到右括号

      // 现在这就是递归发挥作用的地方。我们将使用递归来解决事情而不是尝试去解析可能无限嵌套的节点集
      //
      // 为了解释这个，我们先用 lisp 代码做演示
      // 
      // 可以看到`add` 的参数是一个数字，还有一个包含自己数字的嵌套`CallExpression`
      //   (add 2 (subtract 4 2))
      //
      // 你也将会注意到，在我们的标记数组里，我们有很多右括号
      //
      //   [
      //     { type: 'paren',  value: '('        },
      //     { type: 'name',   value: 'add'      },
      //     { type: 'number', value: '2'        },
      //     { type: 'paren',  value: '('        },
      //     { type: 'name',   value: 'subtract' },
      //     { type: 'number', value: '4'        },
      //     { type: 'number', value: '2'        },
      //     { type: 'paren',  value: ')'        }, <<< 右括号
      //     { type: 'paren',  value: ')'        }, <<< 右括号
      //   ]
      //
      // 我们将依赖嵌套的`walk`函数来增加我们的`current`变量来超过任何嵌套的`CallExpression`
      // 所以我们创建一个`while`循环持续到遇到一个`type`是'paren'并且`value`是右括号的标记
      while (
        (token.type !== 'paren') ||
        (token.type === 'paren' && token.value !== ')')
      ) {
        // 我们调用`walk`方法，这个方法会返回一个`node`节点
        // 我们把这个节点存到我们的`node.params`中去
        node.params.push(walk());
        token = tokens[current];
      }

      // 我们最后一次增加`current`变量来跳过右括号
      current++;

      // 返回node节点
      return node;
    }

    // 同样的，如果我们到这里都没有辨认出标记的类型，就抛出一个异常
    throw new TypeError(token.type);
  }

  // 现在，我们将要创建我们的 AST 树，他有一个根节点叫做`Program`节点
  let ast = {
    type: 'Program',
    body: [],
  };

  // 并且启动我们的`walk`函数，把节点推到我们的`ast.body`数组
  // 我们之所以在一个循环里做这些事是因为我们的程序可以有一个接一个的`CallExpression`而不是嵌套的
  //
  //   (add 2 2)
  //   (subtract 4 2)
  //
  while (current < tokens.length) {
    ast.body.push(walk());
  }

  // 最后返回我们得到的 AST 结构
  return ast;
}

/**
 * ============================================================================
 *                                 ⌒(❀>◞౪◟<❀)⌒
 *                               THE TRAVERSER!!!
 * ============================================================================
 */

/**
 * 现在我们已经有了一个 AST 树。然后我们想要通过访问者（visitor）来访问不同的节点。
 * 无论什么时候只要遇到能匹配类型的节点，就需要调用访问者的方法，像这样：
 *
 *   traverse(ast, {
 *     Program: {
 *       enter(node, parent) {
 *         // ...
 *       },
 *       exit(node, parent) {
 *         // ...
 *       },
 *     },
 *
 *     CallExpression: {
 *       enter(node, parent) {
 *         // ...
 *       },
 *       exit(node, parent) {
 *         // ...
 *       },
 *     },
 *
 *     NumberLiteral: {
 *       enter(node, parent) {
 *         // ...
 *       },
 *       exit(node, parent) {
 *         // ...
 *       },
 *     },
 *   });
 */

// 所以我们定义了一个接收一个 AST 和一个访问者的遍历器函数
// 在里面我们还将定义两个函数...
function traverser(ast, visitor) {

  // 一个`traverseArray`函数，一个`traverseNode`函数
  // traverseArray 函数来迭代数组，并且调用 traverseNode 函数
  function traverseArray(array, parent) {
    array.forEach(child => {
      traverseNode(child, parent);
    });
  }

  // traverseNode 函数将接受两个参数：node 节点和他的 parent 节点
  // 这样他就可以将两者都传递给我们的访问者方法（visitor）
  function traverseNode(node, parent) {

    // 我们首先从匹配`type`开始，来检测访问者方法是否存在。访问者方法就是（enter 和 exit）
    let methods = visitor[node.type];

    // 如果这个节点类型有`enter`方法，我们将调用这个函数，并且传入当前节点和他的父节点
    if (methods && methods.enter) {
      methods.enter(node, parent);
    }

    // 接下去我们将按当前节点类型来进行拆分，以便于对子节点数组进行遍历，处理到每一个子节点
    switch (node.type) {

      // 首先从最高的`Program`层开始。因为 Program 节点有一个名叫 body 的属性，里面包含了节点数组
      // 我们调用`traverseArray`来向下遍历它们
      //
      // 请记住，`traverseArray`会依次调用`traverseNode`，所以这棵树将会被递归遍历
      case 'Program':
        traverseArray(node.body, node);
        break;

      // 接下去我们对`CallExpression`做相同的事情，然后遍历`params`属性
      case 'CallExpression':
        traverseArray(node.params, node);
        break;

      // 对于`NumberLiteral`和`StringLiteral`的情况，由于没有子节点，所以直接 break 即可
      case 'NumberLiteral':
      case 'StringLiteral':
        break;

      // 接着，如果我们没有匹配到上面的节点类型，就抛出一个异常错误
      default:
        throw new TypeError(node.type);
    }

    // 如果这个节点类型里面有一个`exit`方法，我们就调用它，并且传入当前节点和他的父节点
    if (methods && methods.exit) {
      methods.exit(node, parent);
    }
  }

  // 代码最后，我们调用`traverseNode`来启动遍历，传入之前的 AST 树，由于 AST 树最开始
  // 的点没有父节点，所以我们直接传入 null 就好
  traverseNode(ast, null);
}

/**
 * ============================================================================
 *                                   ⁽(◍˃̵͈̑ᴗ˂̵͈̑)⁽
 *                              THE TRANSFORMER!!!
 * ============================================================================
 */

/**
 * 下一步就是转换器了。我们的转换器将获取我们构建的 AST 并将其传递给我们的遍历器函数，并创建一个新的 AST：
 *
 * ----------------------------------------------------------------------------
 *   Original AST                     |   Transformed AST
 * ----------------------------------------------------------------------------
 *   {                                |   {
 *     type: 'Program',               |     type: 'Program',
 *     body: [{                       |     body: [{
 *       type: 'CallExpression',      |       type: 'ExpressionStatement',
 *       name: 'add',                 |       expression: {
 *       params: [{                   |         type: 'CallExpression',
 *         type: 'NumberLiteral',     |         callee: {
 *         value: '2'                 |           type: 'Identifier',
 *       }, {                         |           name: 'add'
 *         type: 'CallExpression',    |         },
 *         name: 'subtract',          |         arguments: [{
 *         params: [{                 |           type: 'NumberLiteral',
 *           type: 'NumberLiteral',   |           value: '2'
 *           value: '4'               |         }, {
 *         }, {                       |           type: 'CallExpression',
 *           type: 'NumberLiteral',   |           callee: {
 *           value: '2'               |             type: 'Identifier',
 *         }]                         |             name: 'subtract'
 *       }]                           |           },
 *     }]                             |           arguments: [{
 *   }                                |             type: 'NumberLiteral',
 *                                    |             value: '4'
 * ---------------------------------- |           }, {
 *                                    |             type: 'NumberLiteral',
 *                                    |             value: '2'
 *                                    |           }]
 *  (sorry the other one is longer.)  |         }
 *                                    |       }
 *                                    |     }]
 *                                    |   }
 * ----------------------------------------------------------------------------
 */

// 这就是我们的转换器函数，他接受一个 lisp 格式的 ast 树。
function transformer(ast) {

  // 我们创建一个像之前的 AST 树一样的新的 AST 树，也有一个 program 节点。
  let newAst = {
    type: 'Program',
    body: [],
  };

  // 接下去我们要使用一些 hack 的小技巧
  // 首先我们在父节点上使用`context`的属性，这样我们就可以把节点放到其父节点的`context`上
  // 通常你会有比这个更好的抽象方法，但是为了我们的目标能实现，这个方法相对简单些
  //
  // 需要注意的是，这个上下文（context）属性只是用来对比新旧 ast 的
  ast._context = newAst.body;

  // 在这里调用遍历器函数并传入我们的旧的 AST 树和访问者方法
  traverser(ast, {

    // 第一个访问者方法是 NumberLiteral 
    NumberLiteral: {
      // 我们将在 enter 方法里面访问他们
      enter(node, parent) {
        // 我们将创建一个也叫做`NumberLiteral`的新节点，并放到父节点的上下文中去
        parent._context.push({
          type: 'NumberLiteral',
          value: node.value,
        });
      },
    },

    // 接下去是 `StringLiteral`
    StringLiteral: {
      enter(node, parent) {
        parent._context.push({
          type: 'StringLiteral',
          value: node.value,
        });
      },
    },

    // 然后, `CallExpression`，这里相对比较复杂一点
    CallExpression: {
      enter(node, parent) {

        // 首先我们创建一个叫`CallExpression`的节点，它带有表示嵌套的标识符“Identifier”
        let expression = {
          type: 'CallExpression',
          callee: {
            type: 'Identifier',
            name: node.name,
          },
          arguments: [],
        };

        // 接下去我们在原有的`CallExpression`节点（node）上定义一个新的上下文
        // 他将引用 `expression`的参数（arguments），这样就可以利用这个数组了
        node._context = expression.arguments;

        // 之后我们将检查父节点是否是`CallExpression`类型
        // 如果不是的话
        if (parent.type !== 'CallExpression') {

          // 我们将用`ExpressionStatement`来包裹`CallExpression`节点
          // 我们这样做的原因是因为单独存在的`CallExpression`在 js 中也可以被当作是声明语句
          expression = {
            type: 'ExpressionStatement',
            expression: expression,
          };
        }

        // 最后我们把我们的`CallExpression`(可能是被包起来的)放到父节点的上下文中去
        parent._context.push(expression);
      },
    }
  });

  // 在转换器方法的最后，我们就能返回我们刚创建的新的 AST 树了
  return newAst;
}

/**
 * ============================================================================
 *                               ヾ（〃＾∇＾）ﾉ♪
 *                            THE CODE GENERATOR!!!!
 * ============================================================================
 */

/**
 * 现在让我们来到我们最后的一个阶段：代码生成。
 * 代码生成器将递归的调用自己来打印树的每一个节点，最后输出一个巨大的字符串。
 */

 function codeGenerator(node) {

  // 还是按照节点的类型来进行分解操作
  switch (node.type) {

    // 如果我们有`Program`节点，我们将映射`body`中的每个节点
    // 并且通过代码生成器来运行他们，用换行符将他们连接起来
    case 'Program':
      return node.body.map(codeGenerator)
        .join('\n');

    // 对于`ExpressionStatement`，我们将在嵌套表达式上调用代码生成器，并添加一个分号
    case 'ExpressionStatement':
      return (
        codeGenerator(node.expression) +
        ';' // << 这是因为保持代码的统一性（用正确的方式编写代码）
      );

    // 对于`CallExpression`我们将打印`callee`, 新增一个左括号
    // 然后映射每一个`arguments`数组的节点，并用代码生成器执行，每一个节点运行完之后加上逗号
    // 最后增加一个右括号
    case 'CallExpression':
      return (
        codeGenerator(node.callee) +
        '(' +
        node.arguments.map(codeGenerator)
          .join(', ') +
        ')'
      );

    // 对于`Identifier`直接返回`node`的名字就好.
    case 'Identifier':
      return node.name;

    // 对于`NumberLiteral`直接返回`node`的值就好.
    case 'NumberLiteral':
      return node.value;

    // 对于`StringLiteral`，在`node`的值的周围添加双引号.
    case 'StringLiteral':
      return '"' + node.value + '"';

    // 如果没有匹配到节点的类型，就抛出异常
    default:
      throw new TypeError(node.type);
  }
}

/**
 * ============================================================================
 *                                  (۶* ‘ヮ’)۶”
 *                         !!!!!!!!THE COMPILER!!!!!!!!
 * ============================================================================
 */

/**
 * 最后! 我们创建了 `compiler` 函数。 在这里，我们将把管道的每个部分连接在一起。
 *
 *   1. input  => tokenizer   => tokens
 *   2. tokens => parser      => ast
 *   3. ast    => transformer => newAst
 *   4. newAst => generator   => output
 */

function compiler(input) {
  let tokens = tokenizer(input);
  let ast    = parser(tokens);
  let newAst = transformer(ast);
  let output = codeGenerator(newAst);

  // 简单的返回输出
  return output;
}

/**
 * ============================================================================
 *                                   (๑˃̵ᴗ˂̵)و
 * !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!YOU MADE IT!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 * ============================================================================
 */

// 这里把所有的东西都导出...
module.exports = {
  tokenizer,
  parser,
  traverser,
  transformer,
  codeGenerator,
  compiler,
};
