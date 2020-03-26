#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "../xlsx/xlsxdocument.h"
#include "../xlsx/xlsxformat.h"
using namespace QXlsx;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Inserimento utenti");
    model = new QSqlQueryModel(this);
    connect(ui->pushButtonRemove,&QPushButton::clicked,this,&MainWindow::eliminaAlunni);
    connect(ui->actionEsci,&QAction::triggered,qApp,&QApplication::quit);
    connect(ui->fileCSV,&QPushButton::clicked,this,&MainWindow::esportaCSV);
    connect(ui->pushButtonExcel,&QPushButton::clicked,this,&MainWindow::esportaExcel);
    connect(ui->pushButtonAlunno,&QPushButton::clicked,this,&MainWindow::insertAlunni);
    connect(ui->actionAbout,&QAction::triggered,this,&MainWindow::informazioni);
    connect(ui->lineEditGruppo,&QLineEdit::editingFinished,this,&MainWindow::editLineFinishedGruppo);
    lista();
}

void MainWindow::editLineFinishedGruppo()
{
    if(!ui->lineEditGruppo->text().contains("/"))
        ui->lineEditGruppo->setText("/"+ui->lineEditGruppo->text());
    else
        ui->lineEditGruppo->setText(ui->lineEditGruppo->text());
}

void MainWindow::lista()
{
    //First Name ,Last Name ,Email Address ,Password ,Org Unit Path
    model->setQuery("select nome,cognome,email,password,gruppo from utenti");
    model->setHeaderData(0,Qt::Horizontal,"First Name");
    model->setHeaderData(1,Qt::Horizontal,"Last Name");
    model->setHeaderData(2,Qt::Horizontal,"Email Address");
    model->setHeaderData(3,Qt::Horizontal,"Password");
    model->setHeaderData(4,Qt::Horizontal,"Org Unit Path");
    ui->tableView->setModel(model);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->verticalHeader()->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_2_clicked()
{
    qApp->quit();
}

void MainWindow::on_pushButton_3_clicked()
{
    if(ui->lineEditGruppo->text().contains("/"))
        return;
    else ui->lineEditGruppo->setText("/");
    if(ui->lineEditDominio->text() == "")
    {
        QMessageBox::warning(this,"Utenti","Attenzione, il dominio o il gruppo non sono stati inseriti");
    }
    else{
        QMessageBox *box= new QMessageBox(this);
        box->setWindowTitle("Utenti");
        box->setText("Il file excel\ndeve essere composto\n");
        box->setInformativeText("dalle sole colonne Nome e Cognome");
        box->setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
        box->setDefaultButton(QMessageBox::Ok);
        int ret = box->exec();
        switch(ret) {
        case QMessageBox::Ok:{
            QString fileName = QFileDialog::getOpenFileName(this, QObject::tr("Apri file xlsx"),
                                                                        "*.xlsx", QObject::tr("File XLSX(*.xlsx);;Tutti i file(*.*)"));

            if (fileName.isEmpty())
            return;
            else {
            QFile file(fileName);

            if (!file.open(QIODevice::ReadOnly)) {
                QMessageBox::information(this, tr("Unable to open file"),
                        file.errorString());
                        return;
            }
            Document xlsx(fileName);
            if(xlsx.dimension().columnCount() > 2)
            {
                QMessageBox::warning(this,"Utenti","Il file contiene più di 2 colonne");
            }
            else{
                for(int i=1; i <= xlsx.dimension().rowCount(); i++)
                {
                    QProgressDialog progressDialog(this);
                    progressDialog.setRange(0, xlsx.dimension().rowCount());
                    progressDialog.setWindowModality(Qt::WindowModal);
                    progressDialog.setWindowTitle(tr("Inserimento alunni"));
                    progressDialog.setValue(i);
                    progressDialog.setLabelText(tr("Inserimento alunni %1 di %2...")
                                                    .arg(i).arg(xlsx.dimension().rowCount()));
                    qApp->processEvents();
                    char pwd[]={'A','B','C','D','E','F','G','H','I','J','K','L','M','N',
                                'O','P','Q','R','S','T','U','V','W','X','Y','Z',
                                'a','b','c','d','e','f','g','h','i','j','k','l','m','n',
                                'o','p','q','r','s','t','u','v','w','x','y','z',
                            '0','1','2','3','4','5','6','7','8','9','@','?','!',';'};

                    QString addChar;
                    for(int z=0;z<12;z++) {
                        addChar+= QString(pwd[rand()%66]);
                    }
                    QSqlQuery query;
                    QString name_surname;
                    QString req = "INSERT INTO utenti VALUES('";
                    if(Cell *name = xlsx.cellAt(i,1)){
                    req.append(QString(name->value().toString().toStdString().c_str()).replace("'","''"));
                    name_surname = QString(name->value().toString().toStdString().c_str()).replace("'","''");
                    req.append("','");
                    }
                    if(Cell *lastname = xlsx.cellAt(i,2)){
                    req.append(QString(lastname->value().toString().toStdString().c_str()).replace("'","''"));
                    name_surname += QString("."+QString(lastname->value().toString().toStdString().c_str()).replace("'","''"));
                    req.append("',");
                    }
                    req.append("'"+QString(name_surname.remove(" ").remove("'").replace("ì","i").replace("à","a").replace("ò","o").toLower()+"@"+ui->lineEditDominio->text().replace("'","''"))+"',"
                    "'"+addChar+"','"+ui->lineEditGruppo->text().replace("'","''")+"'");
                    req.append(");");
                    query.prepare(req);
                    progressDialog.show();
                    progressDialog.update();
                    
                    query.prepare(req);
                    query.exec();
                }
            }
            }
            lista();
            break;
            }
        case QMessageBox::Cancel:
        //Close
        box->close();
        break;
    }
    }
}

void MainWindow::insertAlunni()
{
    if(ui->lineEditDominio->text() == "" || ui->lineEditGruppo->text() == "" ||
        ui->lineEditNome->text() == "" || ui->lineEditCognome->text() == "")
    {
        QMessageBox::warning(this,"Utenti","Attenzione, il nome, il cognome, il dominio o il gruppo non sono stati inseriti");
    }
    else{
        QSqlQuery query;
        char pwd[]={'A','B','C','D','E','F','G','H','I','J','K','L','M','N',
                        'O','P','Q','R','S','T','U','V','W','X','Y','Z',
                        'a','b','c','d','e','f','g','h','i','j','k','l','m','n',
                        'o','p','q','r','s','t','u','v','w','x','y','z',
                    '0','1','2','3','4','5','6','7','8','9','@','?','!',';'};

        QString addChar,name_surname;
        for(int z=0;z<12;z++) {
            addChar+= QString(pwd[rand()%66]);
        }
        name_surname = QString(ui->lineEditNome->text()+"."+ui->lineEditCognome->text()).remove(" ").remove("'").replace("ì","i").replace("à","a").replace("ò","o").toLower()+"@"+ui->lineEditDominio->text().replace("'","''");
        QString req = "INSERT INTO utenti VALUES('"+ui->lineEditNome->text().replace("'","''")+"','"+ui->lineEditCognome->text().replace("'","''")+"','"+name_surname+"','"+addChar+"','/"+ui->lineEditGruppo->text().replace("'","''")+"')";
        query.prepare(req);
        query.exec();
        lista();
    }
}

void MainWindow::eliminaAlunni()
{
    if(model->rowCount() == 0)
        QMessageBox::warning(this,"Utenti","Non esiste nessun utente nella lista");
    else{
        QSqlQuery query;
        query.prepare("delete from utenti");
        query.exec();
        lista();
    }
}

void MainWindow::esportaCSV()
{
    if(model->rowCount() == 0)
        QMessageBox::warning(this,"Utenti","Non esiste nessun utente inserito");
    else{
        QString fileName = QFileDialog::getSaveFileName(this, "Esporta CSV",
                                                        "*.csv","CSV(*.csv);;Tutti i file(*.*)");

        if (fileName.length() != 0) {
                // Aggiunge estensione alla fine del file se non c'è
                if (fileName.indexOf(".csv") < 0) {
                    fileName += ".csv";
                }
            }

        while( model->canFetchMore(QModelIndex()))
            model->fetchMore(QModelIndex());
        int x = 0;
        QString exportdata;

        int counthidden=0, jint = 0;

        while (jint < model->columnCount()) {

        counthidden+=ui->tableView->isColumnHidden(jint);
        jint++;
        }


        int w = 1;
        while (x < model->columnCount()){

        if (!ui->tableView->isColumnHidden(x)) {


        exportdata.append(model->headerData(x,Qt::Horizontal,Qt::DisplayRole).toString());


        if (model->columnCount() - w > counthidden)
        exportdata.append(",");
        else {
        exportdata.append("\n");

        }
        w++;
        }
        x++;

        }

        int z = 0;

        w = 1;
        while (z < model->rowCount()) {

        x = 0;

        w = 1;
        while (x < model->columnCount()) {
        if (!ui->tableView->isColumnHidden(x)) {


        exportdata.append(model->data(model->index(z,x),Qt::DisplayRole).toString());

        if (model->columnCount() - w > counthidden)
        exportdata.append(",");
        else
        exportdata.append("\n");

        w++;
        }
        x++;

        }

        z++;
        }

        QFile file;
        if (!fileName.isEmpty()) {
        file.setFileName(fileName);
                if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
                    return;
        }
        QByteArray ttext;
        ttext.append(exportdata);
        file.write(ttext);
    }
}

void MainWindow::esportaExcel()
{
    if(model->rowCount() == 0)
        QMessageBox::warning(this,"Utenti","Non esiste nessun utente inserito");
    else{
        QString fileName = QFileDialog::getSaveFileName(this, QObject::tr("Esporta Excel"),
                                                                "*.xlsx", QObject::tr("XLSX(*.xlsx);;Tutti i file(*.*)"));


                if (fileName.length() != 0) {
                    // Aggiunge estensione alla fine del file se non c'è
                    if (fileName.indexOf(".xlsx") < 0) {
                        fileName += ".xlsx";
                    }
                }

                Document excel;
                while( model->canFetchMore(QModelIndex()))
                    model->fetchMore(QModelIndex());
                    
                    for(int i= 0; i < model->columnCount(QModelIndex());++i){
                        //Imposto header label per la descrizione
                        Format fm;
                        fm.setFontName("Verdana");
                        fm.setFontBold(true);
                        fm.setFontSize(12);
                        excel.setRowHeight(1,30.0);
                        excel.setRowHeight(2,30.0);
                        excel.setColumnWidth(i,25.0);
                        excel.write(1,7,"Elenco alunni",fm);
                        excel.write(2,1+i,model->headerData(i,Qt::Horizontal,Qt::DisplayRole).toString(),fm);
                        for(int row = 0; row < model->rowCount(QModelIndex()); row++){
                        //Imposto le righe
                        Format fmt;
                        fmt.setFontName("Verdana");
                        fmt.setFontSize(12);
                        excel.setRowHeight(3,30.0);
                        
                        excel.write(3+row,1+i,model->data(model->index(row,i,QModelIndex()),Qt::DisplayRole).toString(),fmt);
                        }
                    }

                    int ris = excel.saveAs(fileName);
                    if(ris != 0)
                        QMessageBox::information(this,"Utenti","File salvato correttamente");
    }
}

void MainWindow::informazioni()
{
    QMessageBox::information(this,"Utenti","<p>Software realizzato per minimizzare il lavoro di caricamento<br>"
        "dei file CSV sulla piattaforma GSuite.<br><b>(C)Copyright 2020. Angelo Scarnà<b></p>");
}