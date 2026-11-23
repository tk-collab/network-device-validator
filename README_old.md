# Network Device Configuration Validator

## 1. 概要

C言語でネットワーク機器のVLAN設定およびポート設定の妥当性を検証するプログラムです。

Unity（ThrowTheSwitch）を使用した単体テストを実装し、境界値分析、異常系テスト、コードカバレッジ計測を行っています。

## 2. 開発環境

| 項目 | 内容 |
|---|---|
| プログラミング言語 | C |
| C言語規格 | C11 |
| コンパイラ | GCC 16.2.0 |
| テストフレームワーク | Unity |
| 開発環境 | MSYS2 UCRT64 |
| カバレッジ計測 | gcov |

Unity commit: 54f864c

## 3. 実装機能

### VLAN ID validation
- VLAN IDの有効範囲：1～4094
- 配列による複数VLAN IDの検証
- ポインタを利用した配列要素の参照
- NULLポインタのチェック

### VLAN ID list validation
- 構造体によるVLAN IDと要素数の管理
- 最大16個のVLAN IDを格納
- 配列容量の境界チェック

### Port configuration validation
- enumによるポートモードの管理
- ACCESSモード：VLAN IDを1個指定
- TRUNKモード：VLAN IDを1～16個指定
- 未定義のポートモードの拒否

※ポート設定のルールは本プロジェクトで定義した学習用の仕様です。

## 4. テスト設計

Unityを使用して単体テストを自動実行しています。

主なテスト観点：
- 正常系・異常系
- 境界値分析（Boundary Value Analysis）
- 配列・ポインタの検証
- NULLポインタの検証
- 構造体・enumの検証
- 配列容量の上限・超過
- ACCESS / TRUNKの条件分岐

## 5. テスト結果

| 項目 | 結果 |
|---|---:|
| テストケース数 | 39 |
| 成功 | 39 |
| 失敗 | 0 |

### Code Coverage

GCC gcovによる計測結果：

| 指標 | 結果 |
|---|---:|
| 行カバレッジ | 100%（34/34） |
| 分岐実行率 | 100%（25/25） |
| 分岐実行確認率 | 100%（25/25） |

対象：config_validator.c

※カバレッジ100%は、プログラムに不具合が存在しないことを保証するものではありません。

## 6. ビルド・実行方法

### Compile

```bash
gcc -std=c11 -Wall -Wextra -I. config_validator.c test_config_validator.c unity/src/unity.c -o test_runner
```
### Run

```bash
./test_runner
```

## 7. プロジェクトの制限事項
本プロジェクトはホスト環境上での単体テストを目的としています。

実際のネットワーク機器への設定投入、実機検証、ネットワーク通信試験は実施していません。
