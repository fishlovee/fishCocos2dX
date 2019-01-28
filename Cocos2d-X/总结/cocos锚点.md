## 锚点

- CCNode的锚点为(0.5,0.5)
- CCLayer的锚点默认为(0,0)，即左下角。并且忽略锚点的设置，即使你setAnchorPoint了锚点，CCLayer的锚点也不会改变，依然是（0,0）。
- CCSprite的的锚点默认为(0.5,0.5)，即中心点。
- CCRect的锚点为左下角，若用CCRect来作为创建CCSprite精灵的参数，需要注意，从大图中截取某一区域的图片的CCRect rect的构造应该是：CCRect("小图左上角坐标x", "小图左上角坐标y", 小图宽, 小图高);
- CCMenu的父类为CCLayer，所以锚点为（0,0），且无法设置锚点。
- CCMenuItem的父类为CCNode，因此锚点为(0.5,0.5)。对于CCMenuItem是添加在CCMenu层中的，所以CCMenuItem的位置是相对于CCMenu层的偏移位置。CCMenuItem相对于CCMenu的偏移量默认为（0,0），且菜单项的锚点默认为（0.5,0.5）。